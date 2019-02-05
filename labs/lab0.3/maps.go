package main

import (
    "golang.org/x/tour/wc"
    "strings"
)

func WordCount(s string) map[string]int {

	var wordMap map[string]int
	var word string
	
    wordMap = make(map[string]int)
    for _ ,word= range strings.Fields(s){
        wordMap[word]++
    }
return wordMap
}

func main() {
    wc.Test(WordCount)
}
