package main

import "fmt"

var Usage = func() {
	fmt.Println("hello")
}

func f() {
	fmt.Println("hello")
}

var (
	a, b = 1, 2
)

var c, d = 1, 2

func main() {
	Usage()
	f()
	var a = 1 // 自动推断
	println(a)

	var b int = 2
	// b = 2.2 // error
	println(b)

	var c float64
	println(c) // 默认值

	d := 1 // 省略 var
	print(d)

	i, j, k := 1, 2, 3
	i, j, k = 2, 3, 4
	print(i)
	print(j)
	print(k)

	var ii, jj = 1, 2
	ii, jj = 2, 3
	print(ii)
	print(jj)

	var iii, jjj int = 1, 2
	iii, jjj = 2, 3
	print(iii)
	print(jjj)

	var (
		i2, j2 = 1, 2
	)
	print(i2)
	print(j2)

}
