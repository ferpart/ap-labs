// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 254.
//!+

// Chat is a server that lets clients chat with each other.
package main

import (
	"bufio"
	"flag"
	"fmt"
	"log"
	"net"
	"regexp"
	"strings"
	"time"
)

//!+broadcaster
type client chan<- string // an outgoing message channel

var (
	entering    = make(chan client)
	leaving     = make(chan client)
	messages    = make(chan string) // all incoming client messages
	users       = make(map[string]net.Conn)
	connections int
	serverMsg   = "irc-server >"
)

func broadcaster() {
	clients := make(map[client]bool) // all connected clients
	for {
		select {
		case msg := <-messages:
			// Broadcast incoming message to all
			// clients' outgoing message channels.
			for cli := range clients {
				cli <- msg
			}

		case cli := <-entering:
			clients[cli] = true

		case cli := <-leaving:
			delete(clients, cli)
			close(cli)
		}
	}
}

//!-broadcaster

//!+handleConn
func handleConn(conn net.Conn) {
	ch := make(chan string) // outgoing client messages
	who := ""

	go clientWriter(conn, ch)

	connections++

	input := bufio.NewScanner(conn)
	for input.Scan() {

		mssg := input.Text()

		if matches, _ := regexp.MatchString("^<user>.+", mssg); matches {
			separatedString := strings.Split(mssg, ">")
			who = separatedString[1]

			fmt.Printf("%s New connected user %s\n", serverMsg, who)

			ch <- serverMsg + " Welcome to the Simple IRC Server"
			ch <- serverMsg + " Your user " + who + " is successfully logged"
			messages <- serverMsg + " " + who + " has arrived"
			entering <- ch

			users[who] = conn

		} else if mssg == "/help" {
			fmt.Fprintf(conn, "The following commands are avaiable\n/users\n/msg <user> <msg>\n/time\n/user <user>\n")
		} else if mssg == "/users" {
			fmt.Fprintf(conn, "%s ", serverMsg)
			for key := range users {
				fmt.Fprintf(conn, " %s", key)
			}
			fmt.Fprintf(conn, "\n")
		} else if mssg == "/time" {
			t := time.Now()
			zone, _ := t.Zone()
			timeFormated := t.Format("03:04")
			fmt.Fprintf(conn, "%s Local Time: %s %s\n", serverMsg, zone, timeFormated)
		} else if matches, _ := regexp.MatchString("^/user .+$", mssg); matches {
			separatedString := strings.Split(mssg, " ")
			if user, exists := users[separatedString[1]]; exists {
				fmt.Fprintf(conn, "%s username: %s, IP: %s\n", serverMsg, separatedString[1], user.RemoteAddr().String())
			} else {
				fmt.Fprintf(conn, "%s user: %s does not exist\n", serverMsg, separatedString[1])
			}
		} else if matches, _ := regexp.MatchString("/msg .+ .+", mssg); matches {
			separatedString := strings.Split(mssg, " ")
			numMesseges := len(separatedString)
			if dmUser, exists := users[separatedString[1]]; exists {
				fmt.Fprintf(dmUser, "%s >", who)
				for i := 2; i < numMesseges; i++ {
					fmt.Fprintf(dmUser, " %s", separatedString[i])
				}
				fmt.Fprintf(dmUser, "\n")
			} else {
				fmt.Fprintf(conn, "%s user: %s does not exist\n", serverMsg, separatedString[1])
			}
		} else if matches, _ := regexp.MatchString("^/.+$", mssg); matches {
			separatedString := strings.Split(mssg, " ")
			fmt.Fprintf(conn, "%s %s does not exist. for avaiable commands use '/help'\n", serverMsg, separatedString[0])
		} else {
			messages <- who + "> " + input.Text()
		}

		//println(input.Text())
	}
	// NOTE: ignoring potential errors from input.Err()

	leaving <- ch
	messages <- serverMsg + " " + who + " left"
	conn.Close()
}

func clientWriter(conn net.Conn, ch <-chan string) {
	for msg := range ch {
		fmt.Fprintln(conn, msg) // NOTE: ignoring network errors
		//fmt.Fscanln(conn)
	}
}

//!-handleConn

//!+main
func main() {

	host := flag.String("host", "localhost", "host String")
	port := flag.String("port", "9000", "port String")

	flag.Parse()

	fmt.Printf("%s Simple IRC Server started at %s:%s\n", serverMsg, *host, *port)
	fmt.Printf("%s Ready for receiving new clients\n", serverMsg)

	listener, err := net.Listen("tcp", *host+":"+*port)
	if err != nil {
		log.Fatal(err)
	}

	go broadcaster()
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Print(err)
			continue
		}
		go handleConn(conn)
	}
}

//!-main
