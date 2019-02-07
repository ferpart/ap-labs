## Golang Basics (Lab 0.3)

For this lab we have been assigned to do 3 different exercises to learn about the Go language. 

### Firstly the Slices problem taken from: [Exercise: Slices](https://tour.golang.org/moretypes/18) 

#### The problem states

Implement Pic. It should return a slice of length dy, each element of which is a slice of dx 8-bit unsigned integers. When you run the program, it will display your picture, interpreting the integers as grayscale (well, bluescale) values.

The choice of image is up to you. Interesting functions include (x+y)/2, x*y, and x^y.

(You need to use a loop to allocate each []uint8 inside the [][]uint8.)

(Use uint8(intValue) to convert between types.) 

```go
package main

import "golang.org/x/tour/pic"

func Pic(dx, dy int) [][]uint8 {
	matrix := make([][]uint8, dy, dy)
	for i := range matrix {
		matrix[i] = make([]uint8, dx, dx)
		for j := range matrix[i] {
			matrix[i][j] = uint8((i+j)/2)
		}
	}
	return matrix
}

func main() {
	pic.Show(Pic)
}
```

### Secondly the Maps problem taken from: [Exercise: Maps](https://tour.golang.org/moretypes/23) 

#### The problem states

Implement WordCount. It should return a map of the counts of each “word” in the string s. The wc.Test function runs a test suite against the provided function and prints success or failure.

You might find strings.Fields helpful. 

```go
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
```

### Thirdly changing a code from a git repository taken from: [Alan Donovan's geometry.go](https://github.com/adonovan/gopl.io/blob/master/ch6/geometry/geometry.go)

#### The problem states

1. **Copy** the code from:

https://github.com/adonovan/gopl.io/blob/master/ch6/geometry/geometry.go

2. **Paste** at:

https://play.golang.org/

3. Change **X** and **Y** to **x** and **y** in **Point** structure
4. Create the **X** and **Y** methods

5. Add a function **printPoint** that recieves a **Point** and prints **x** and **y**

6. Add **main()** to use the **printFunction**

#### The code taken from Alan Donovan's Github page is the following:
```go
// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 156.

// Package geometry defines simple types for plane geometry.
//!+point
package geometry

import "math"

type Point struct{ X, Y float64 }

// traditional function
func Distance(p, q Point) float64 {
	return math.Hypot(q.X-p.X, q.Y-p.Y)
}

// same thing, but as a method of the Point type
func (p Point) Distance(q Point) float64 {
	return math.Hypot(q.X-p.X, q.Y-p.Y)
}

//!-point

//!+path

// A Path is a journey connecting the points with straight lines.
type Path []Point

// Distance returns the distance traveled along the path.
func (path Path) Distance() float64 {
	sum := 0.0
	for i := range path {
		if i > 0 {
			sum += path[i-1].Distance(path[i])
		}
	}
	return sum
}

//!-path
```

### Finally in order to run the programs, one needs to salect any of the go files and run them in [The Go Playground](https://play.golang.org/)

This can be done following the next link:

https://play.golang.org/


 
