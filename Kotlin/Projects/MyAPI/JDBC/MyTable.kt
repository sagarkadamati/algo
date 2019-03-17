package MyAPI.JDBC

import MyAPI.JDBC.MyDB

class MyTable(tdb: MyDB, table: String, td :ArrayList<HashMap<String, Any>>) {
	private var tDB: MyDB
	private var tName: String
	private var tData: ArrayList<HashMap<String, Any>>

	public var size: Int = 0
		get() = tData.size

	init {
		tDB   = tdb
		tName = table
		tData = td
	}

	fun setTableData(td :ArrayList<HashMap<String, Any>>) {
		tData = td
	}

	fun addColumn(column: String, type: Any) {
		tDB.addColumn(tName, column, type)
		tDB.updateMyTable(tName, this)
	}

	fun addRow(tuple: HashMap<String, Any>) {
		tDB.addRow(tName, tuple);
		tData.add(tuple)
		tDB.updateMyTable(tName, this)
	}

	operator fun get(row: Int): HashMap<String, Any> {
		return tData[row - 1]
	}

	operator fun get(row: Int, column: String): Any? {
		return tData[row - 1][column]
	}

	operator fun set(row: Int, tuple: HashMap<String, Any>) {
		tuple["id"] = row
		tDB.updateRow(tName, tuple)
		tDB.updateMyTable(tName, this)
	}

	operator fun set(row: Int, column: String, uData: Any) {
		tData[row - 1][column] = uData
		tDB.updateRow(tName, tData[row - 1])
		tDB.updateMyTable(tName, this)
	}

	fun dropColumn(column: String) {
		tDB.dropColumn(tName, column)
		tDB.updateMyTable(tName, this)
	}

	fun dropRow(row: Int) {
		tDB.dropRow(tName, row)
		tDB.updateMyTable(tName, this)
	}

	fun drop() {
		tDB.dropTable(tName)
	}
}