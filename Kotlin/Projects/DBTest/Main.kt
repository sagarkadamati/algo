import MyAPI.JDBC.MyDB

fun main(args: Array<String>) {
	var db = MyDB("test.db")
	db.enableDBG()

	var tuple = HashMap<String, Any>()
	tuple["id"] = 1
	tuple["name"] = "this is modified"

	println(db.tables)
	db.table = "Test"
	db + "name TEXT"
	db + "name TEXT"
	db - "name"
	db + "name TEXT"

	db + tuple

	var table = db["Test"]
	table.forEach {
		row -> row.forEach {
			column ->
			println(column)
		}
	}
	// println(table[0]["id"])

	// tuple = db.query(tuple)

	// tuple["name"] = "test"
	// db.update(tuple)
	// tuple = db.query(tuple)
	// println("ID : " + tuple["id"] + ", Name = " + tuple["name"])

	// db - "ramu"
	// db.dropTable()
}