fun testArgs(args: Array<String>) {
	for (arg in args) {
		println("args: $arg")
	}
}

fun main(args: Array<String>) {
	testArgs(args)
}