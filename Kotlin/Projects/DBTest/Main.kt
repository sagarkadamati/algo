import MyAPI.JDBC.MyDB

fun main(args: Array<String>) {
	var db = MyDB("test.db")
	println(db.tables)
	db.fields = "name TEXT"
	db.table = "Test"

	var data = HashMap<String, Any>()
	data["id"] = 10
	data["name"] = "hello"
	db + data
	data = db.query(data)

	data["name"] = "test"
	// db.debug = true
	db.update(data)
	data = db.query(data)
	println("ID : " + data["id"] + ", Name = " + data["name"])
}