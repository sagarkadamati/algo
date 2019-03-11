package MyAPI.JDBC

import java.sql.Connection
import java.sql.DriverManager
import java.sql.ResultSet
import java.sql.Statement
import java.sql.DatabaseMetaData
import java.sql.SQLException
import java.sql.PreparedStatement
import java.sql.Types
import java.sql.ResultSetMetaData

class MyDB(db: String) {
	enum class ERROR {
		SUCCESS,
		ERROR
	}

	private var conn: Connection ?= null
	private var statement: Statement ?= null
	private var resultSet: ResultSet ?= null

	var tables: ArrayList<String> = ArrayList<String>()

	private var row = HashMap<String, Any>()

	private var Error = ERROR.SUCCESS
	private var iTable: String = ""
	var debug = false

	var fields: String = ""
	var table: String get() = iTable
		set(tName: String) {
			loadTable(tName)
		}

	init {
		try {
			conn = DriverManager.getConnection("jdbc:sqlite:${db}")
			statement = conn!!.createStatement()

			loadTables()
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			e.printStackTrace()
		}
	}

	private fun loadTables() {
		try {
			val sql = "Select name From sqlite_master where type='table' order by name"
			resultSet = statement!!.executeQuery(sql)
			while (resultSet!!.next()) {
					tables.add(resultSet!!.getString(1))
			}
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			e.printStackTrace()
		}
	}

	fun loadTable(table: String) {
		create(table)
	}

	fun create(table: String) {
		var sql: String = "CREATE TABLE IF NOT EXISTS ${table} ( id integer PRIMARY KEY "
		sql += if (fields.trim().isNotEmpty()) ", ${fields} )" else " )"

		try {
			statement!!.execute(sql)
			iTable = table
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			e.printStackTrace()
		}

		// // Simple queries
		//
		// CREATE TABLE IF NOT EXISTS materials (
		//id integer PRIMARY KEY,
		//description text NOT NULL
		// )
		//
		// CREATE TABLE IF NOT EXISTS inventory (
		//warehouse_id integer,
		//material_id integer,
		//qty real,
		//PRIMARY KEY (warehouse_id, material_id),
		//FOREIGN KEY (warehouse_id) REFERENCES warehouses (id),
		//FOREIGN KEY (material_id) REFERENCES materials (id)
		// )
	}

	operator fun plus(hm: HashMap<String, Any>) {
		if (hm["id"] == 0)
			addRow(hm)
		else
			updateRow(hm)
	}

	operator fun minus(hm: HashMap<String, Any>) {
		dropRow(hm)
	}

	operator fun plus(column: String) {
		addColumn(column)
	}

	operator fun minus(column: String) {
		dropColumn(column)
	}

	operator fun get(lTable: String): ArrayList<HashMap<String, Any>> {
		return getTable(lTable)
	}

	fun addColumn(column: String) {
		try {
			var sql = "PRAGMA table_info ( ${iTable} )"
			val cName = column.split(" ")[0]
			var found = false
	
			if (debug) println(sql)

			resultSet = statement!!.executeQuery(sql)
			while (resultSet!!.next()) {
				// ID = 1, Column Name, Column Type, ... etc
				if (resultSet!!.getString(2) == cName) {
					found = true
				}
			}
			if (!found) {
				sql = "ALTER TABLE ${iTable} ADD COLUMN ${column}"
				statement!!.execute(sql)
			}
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			e.printStackTrace()
		}
	}

	fun dropColumn(column: String) {
		try {
			var sql = "PRAGMA table_info ( ${iTable} )"
			if (debug) println(sql)

			resultSet = statement!!.executeQuery(sql)

			sql = "CREATE TABLE ${iTable}_backup AS SELECT id"
			while (resultSet!!.next()) {
				var key = resultSet!!.getString(2)

				println(key)
				// ID = 1, Column Name, Column Type, ... etc
				// FIXME: id:1
				if (key == column || key == "id" || key == "id:1") continue

				sql += ", ${key}"
			}
			sql += " FROM ${iTable}"

			if (debug) println(sql)
			statement!!.execute(sql)
			statement!!.execute("DROP TABLE ${iTable}")
			statement!!.execute("ALTER TABLE ${iTable}_backup RENAME TO ${iTable}")
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			e.printStackTrace()
		}
	}

	fun addRow(hm: HashMap<String, Any>) {
		var size = hm.size
		var fields = "INSERT INTO ${iTable} ( "
		var values = " VALUES ( "

		for(key in hm.keys) {
			size--
			if (key == "id") continue

			fields += key + if (size > 1) ", " else ""
			values += "?" + if (size > 1) ", " else ""
		}
		fields += " )"
		values += " )"

		try {
			if (debug)
				println(fields + values + size)
			var pstmt: PreparedStatement = conn!!.prepareStatement(fields + values)
			var index = 1
			for(key in hm.keys) {
				if (key != "id") {
					val item = hm[key]
					when(item) {
						is Short -> pstmt.setShort(index++,item)
						is Int -> pstmt.setInt(index++,item)
						is Long -> pstmt.setLong(index++, item)
						is Float -> pstmt.setFloat(index++,item)
						is Double -> pstmt.setDouble(index++, item)
						is String -> pstmt.setString(index++, item)
						else -> println("Type Not found to insert into db")
					}
				}
			}
			pstmt.executeUpdate()
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			e.printStackTrace()
		}
	}

	fun dropRow(hm: HashMap<String, Any>) {
		try {
			var pstmt: PreparedStatement = conn!!.prepareStatement("DELETE FROM ${iTable} WHERE id = ?")
			pstmt.setInt(1, hm["id"] as Int)
			pstmt.execute()
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			e.printStackTrace()
		}
	}

	fun updateRow(hm: HashMap<String, Any>) {
		var sql = "UPDATE ${iTable} SET "
		for(key in hm.keys) {
			if (key != "id") {
				sql += "${key} = ? "
			}
		}
		sql += "WHERE id = ?"
		if (debug)
			println(sql)

		try {
			var pstmt: PreparedStatement = conn!!.prepareStatement(sql)
			var index = 1
			for(key in hm.keys) {
				if (key != "id") {
					val item = hm[key]
					when(item) {
						is Short -> pstmt.setShort(index++,item)
						is Int -> pstmt.setInt(index++,item)
						is Long -> pstmt.setLong(index++, item)
						is Float -> pstmt.setFloat(index++,item)
						is Double -> pstmt.setDouble(index++, item)
						is String -> pstmt.setString(index++, item)
						else -> println("Type Not found to insert into db")
					}
				}
			}
			pstmt.setInt(index, hm["id"] as Int)
			pstmt.execute()
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			e.printStackTrace()
		}
	}

	fun dropTable() {
		try {
			val sql = "DROP TABLE IF EXISTS ${iTable}"
			statement!!.execute(sql)
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			e.printStackTrace()
		}
	}

	fun query(hm: HashMap<String, Any>): ArrayList<HashMap<String, Any>> {
		var hmList = ArrayList<HashMap<String, Any>>()

		var sql = "SELECT id"
		for(key in hm.keys) {
			if (key != "id") {
				sql += ", " + key
			}
		}
		sql += " FROM ${iTable}"
		if (debug)
			println(sql)

		try {
			resultSet = statement!!.executeQuery(sql)
			while (resultSet!!.next()) {
				var hmColumn = HashMap<String, Any>()
				var md: ResultSetMetaData = resultSet!!.getMetaData()
				for (index in  1..md.getColumnCount()) {
					var cName = md.getColumnName(index)
					var cType  = md.getColumnType(index)

					hmColumn[cName] = when(cType) {
						Types.INTEGER -> resultSet!!.getInt(index)
						Types.FLOAT -> resultSet!!.getFloat(index)
						Types.DOUBLE -> resultSet!!.getDouble(index)
						else -> resultSet!!.getString(index)
					}
				}
				hmList.add(hmColumn)
			}
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			e.printStackTrace()
		}

		if (debug) {
			var rowOut = ""
			for(key in hm.keys) {
				rowOut += "${hm[key]}, "
			}
			println("Row: ${rowOut}")
		}

		return hmList
	}

	fun getTable(lTable: String): ArrayList<HashMap<String, Any>> {
		var hmList = ArrayList<HashMap<String, Any>>()

		try {
			resultSet = statement!!.executeQuery("SELECT * FROM ${lTable}")
			while (resultSet!!.next()) {
				var hmColumn = HashMap<String, Any>()
				var md: ResultSetMetaData = resultSet!!.getMetaData()
				for (index in  1..md.getColumnCount()) {
					var cName = md.getColumnName(index)
					var cType  = md.getColumnType(index)

					hmColumn[cName] = when(cType) {
						Types.INTEGER -> resultSet!!.getInt(index)
						Types.FLOAT -> resultSet!!.getFloat(index)
						Types.DOUBLE -> resultSet!!.getDouble(index)
						else -> resultSet!!.getString(index)
					}
				}
				hmList.add(hmColumn)
			}
			iTable = lTable
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			e.printStackTrace()
		}

		return hmList
	}

	protected fun finalize() {
		try	{
			if (resultSet != null)	resultSet!!.close()
			if (statement != null)	statement!!.close()
			if (conn != null) conn!!.close()
		} catch (e: Exception) {
			Error = ERROR.ERROR
			e.printStackTrace()
		}
	}
}