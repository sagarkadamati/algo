package MyAPI.JDBC

import java.sql.Connection
import java.sql.DriverManager
import java.sql.ResultSet
import java.sql.Statement
import java.sql.DatabaseMetaData
import java.sql.SQLException
import java.sql.PreparedStatement

class MyDB(db: String) {
	enum class ERROR {
		SUCCESS,
		ERROR
	}

	private var conn: Connection ?= null
	private var statement: Statement ?= null
	private var resultSet: ResultSet ?= null

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

			// var meta: DatabaseMetaData = conn.getMetaData()
			// println("The driver name is " + meta.getDriverName())
			// println("A new database has been created.")
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			println(e)
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
			iTable = table;
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			println(e)
		}

		// // Simple queries
		//
		// CREATE TABLE IF NOT EXISTS materials (
		//  id integer PRIMARY KEY,
		//  description text NOT NULL
		// );
		//
		// CREATE TABLE IF NOT EXISTS inventory (
		//  warehouse_id integer,
		//  material_id integer,
		//  qty real,
		//  PRIMARY KEY (warehouse_id, material_id),
		//  FOREIGN KEY (warehouse_id) REFERENCES warehouses (id),
		//  FOREIGN KEY (material_id) REFERENCES materials (id)
		// );
	}

	operator fun plusAssign(hm: HashMap<String, Any>) {
		if (hm["id"] == 0)
			add(hm)
		else
			update(hm)
	}

	operator fun minusAssign(hm: HashMap<String, Any>) {
		try {
			var pstmt: PreparedStatement = conn!!.prepareStatement("DELETE FROM ${iTable} WHERE id = ?")
			pstmt.setInt(1, hm["id"] as Int)
			pstmt.executeUpdate()
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			println(e)
		}
	}

	fun add(hm: HashMap<String, Any>) {
		var size   = hm.size
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
						is Short  -> pstmt.setShort(index++,  item)
						is Int    -> pstmt.setInt(index++,    item)
						is Long   -> pstmt.setLong(index++,   item)
						is Float  -> pstmt.setFloat(index++,  item)
						is Double -> pstmt.setDouble(index++, item)
						is String -> pstmt.setString(index++, item)
						else      -> println("Type Not found to insert into db")
					}
				}
			}
			pstmt.executeUpdate()
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			println(e)
		}
	}

	fun update(hm: HashMap<String, Any>) {
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
						is Short  -> pstmt.setShort(index++,  item)
						is Int    -> pstmt.setInt(index++,    item)
						is Long   -> pstmt.setLong(index++,   item)
						is Float  -> pstmt.setFloat(index++,  item)
						is Double -> pstmt.setDouble(index++, item)
						is String -> pstmt.setString(index++, item)
						else      -> println("Type Not found to insert into db")
					}
				}
			}
			pstmt.setInt(index, hm["id"] as Int)
			pstmt.executeUpdate()
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			println(e)
		}
	}

	fun query(hm: HashMap<String, Any>): HashMap<String, Any> {
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
            // while (resultSet.next()) {
				for(key in hm.keys) {
					when(hm[key]) {
						is Short  -> hm[key] = resultSet!!.getShort(key)
						is Int    -> hm[key] = resultSet!!.getInt(key)
						is Long   -> hm[key] = resultSet!!.getLong(key)
						is Float  -> hm[key] = resultSet!!.getFloat(key)
						is Double -> hm[key] = resultSet!!.getDouble(key)
						is String -> hm[key] = resultSet!!.getString(key)
						else      -> println("Type Not found to insert into db")
					}
				}
			// }
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			println(e)
		}

		if (debug) {
			var rowOut = ""
			for(key in hm.keys) {
				rowOut += "${hm[key]}, "
			}
			println("Row: ${rowOut}")
		}

		return hm;
	}

	fun insert(name: String, capacity: Double) {
		var sql: String = "INSERT INTO ${iTable} (name, capacity) VALUES(?,?)"

		try {
			var pstmt: PreparedStatement = conn!!.prepareStatement(sql)

			pstmt.setString(1, name)
			pstmt.setDouble(2, capacity)
			pstmt.executeUpdate()
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			println(e)
		}
	}

	fun update(id: Int, name: String, capacity: Double) {
		var sql: String = "UPDATE ${iTable} SET name = ? , capacity = ? WHERE id = ?"

		try {
			var pstmt: PreparedStatement = conn!!.prepareStatement(sql)

			// set the corresponding param
			pstmt.setString(1, name)
			pstmt.setDouble(2, capacity)
			pstmt.setInt(3, id)

			// update
			pstmt.executeUpdate()
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			println(e)
		}
	}

	fun deleteRow(id: Int) {
		var sql: String = "DELETE FROM ${iTable} WHERE id = ?"

		try {
			var pstmt: PreparedStatement = conn!!.prepareStatement(sql)

			// set the corresponding param
			pstmt.setInt(1, id)
			// execute the delete statement
			pstmt.executeUpdate()

		} catch (e: SQLException) {
			Error = ERROR.ERROR
			println(e)
		}
	}

	protected fun finalize() {
		try	{
			if (resultSet != null)
				resultSet!!.close()

			if (statement != null)
				statement!!.close()

			if (conn != null)
				conn!!.close()
		} catch (e: Exception) {
			Error = ERROR.ERROR
			e.printStackTrace()
		}
	}
}