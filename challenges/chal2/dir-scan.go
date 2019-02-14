package main

import (
	"fmt"
	"os"
	"io/ioutil"
	"log"
)

// scanDir stands for the directory scanning implementation
func scanDir(dir string) error {

	dirs, perm, symb, other := 0, 0, 0, 0


	files, err := ioutil.ReadDir(dir)
	if err != nil {
		log.Fatal(err)
	}

	for _, f := range files {
		/*if (f.IsDir()){
			dirs++
		}*/
		
		switch mode := f.Mode(); {
			case mode.IsDir():
				dirs++
			case mode&os.ModeSymlink!=0:
				symb++
			case mode.Perm()==0:
				perm++
			default:
				other++
		}
	}
	
	fmt.Println("Directories ", dirs)
	fmt.Println("Permission denied files ", perm)
	fmt.Println("Symbolic links ", symb)
	fmt.Println("Other Files ", other)

	return nil
}

func main() {

	if len(os.Args) < 2 {
		fmt.Println("Usage: ./dir-scan <directory>")
		os.Exit(1)
	}

	scanDir(os.Args[1])
}
