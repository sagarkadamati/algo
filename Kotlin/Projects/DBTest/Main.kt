import MyAPI.JDBC.MyDB

fun main(args: Array<String>) {
	var md = MyDB("test.db")
	md.close()
}