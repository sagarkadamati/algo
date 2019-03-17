import MyAPI.JDBC.MyDB
import MyAPI.JDBC.MyTable

fun main(args: Array<String>) {
	var tuple = HashMap<String, Any>()
	var db = MyDB("test.db")
	db.enableDBG()
	println(db.tables)

	var test = db["Test"]

	println(db.tables)

	println("Size: " + test.size)
	test.addColumn("Name", "")

	// tuple["id"] = 0
	tuple["name"] = "Row 1"
	test.addRow(tuple)

	tuple["name"] = "Row 2"
	test.addRow(tuple)

	tuple["name"] = "Row 3"
	test.addRow(tuple)

	tuple["name"] = "Row 4"
	test.addRow(tuple)

	tuple["name"] = "Row 5"
	test.addRow(tuple)

	test.addColumn("NewCol", "")

	println("Size: " + test.size)

	test[1]["NewCol"] = "New col updated Row 1"
	test[2]["NewCol"] = "New col updated Row 2"
	test[3]["NewCol"] = "New col updated Row 3"
	test[4]["NewCol"] = "New col updated Row 4"
	test[5]["NewCol"] = "New col updated Row 5"

	println("Size: " + test.size)
	for (i in 1..test.size) {
		println("ID: " + test[i]["id"] + ", Name: " + test[i]["Name"] + ", NewCol: " + test[i]["NewCol"])
	}

	test.dropRow(3)
	tuple["Name"] = "Row 6"
	tuple["NewCol"] = "Row 6"
	test.addRow(tuple)

	test[2]["Name"] = "Hey, I'm get modified"

	println("Size: " + test.size)
	for (i in 1..test.size) {
		println("ID: " + test[i]["id"] + ", Name: " + test[i]["Name"] + ", NewCol: " + test[i]["NewCol"])
	}

	test.dropColumn("Name")

	println("Size: " + test.size)
	for (i in 1..test.size) {
		println("ID: " + test[i]["id"] + ", Name: " + test[i]["Name"] + ", NewCol: " + test[i]["NewCol"])
	}

	test.drop()
}