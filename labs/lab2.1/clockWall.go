package main

import (
	"fmt"
	"log"
	"io"
	"os"
	"net"
	"strings"
	"sync"
	"bytes"
)

var wg sync.WaitGroup

func connectionLookup(location string, socket string){
	defer wg.Done()

	connection, err := net.Dial("tcp", socket)

	if err!= nil {
		log.Fatal(err)
		return;
	}

	defer connection.Close()

	for {
		buffer := bytes.NewBufferString(location+" ")
		_, err := io.CopyN(buffer, connection, 9)
		if err != nil {
			log.Fatal(err)
			return;
		}
		fmt.Printf("%s\n", buffer.String())
	}
}

func main(){
	if len(os.Args) < 2{
		return;
	}
	wg.Add(len(os.Args)-1)

	for i := 1; i< len(os.Args); i++ {
		s := strings.Split(os.Args[1], "=")
		x,y := s[0], s[1]
		go connectionLookup(x, y)
	}
	wg.Wait()
}
