# Lab 2.5 - Depth-limiting Web Crawler

For this laboratory we were assigned to do a web crawler in teams of two. For this laboratory my team member is Cesar Augusto Garcia Perez.

For Cesar's git go to [Cesar's ap-labs github](https://github.com/cesarau04/ap-labs "ap-labs cesarau04")

Add depth-limiting to the concurrent web crawler from [crawl2.go](https://github.com/CodersSquad/hello-gophers/blob/master/src/crawl2.go).
That is, if the user sets `-depth=3`, then only URLs reachable by at most 3 links will be fetched.


General Requirements and Considerations
---------------------------------------
- Use the `crawl3.go` file for your implementation.
- Update `README.md` with the proper steps for building and running your code.
- Don't forget to handle errors properly.
- Coding best practices implementation will be also considered.


Test Cases
==========
Your program will be tested with the following URLs:

```
# Test 1
go run crawl3.go -depth=2 https://google.com/

# Test 2
go run crawl3.go -depth=3 http://www.gopl.io/

# Test 3
go run crawl3.go -depth=1  http://www.gopl.io/

```

# How to run

```
go run crawl3.go -depth=2 https://google.com/
go run crawl3.go -depth=3 http://www.gopl.io/
go run crawl3.go -depth=1  http://www.gopl.io/
```
