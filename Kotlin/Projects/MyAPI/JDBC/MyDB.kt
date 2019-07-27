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

import java.sql.Date
import java.sql.Time
import java.sql.Timestamp
import java.sql.Clob
import java.sql.Blob
import java.sql.Array
import java.sql.Ref
import java.sql.Struct

import java.math.BigDecimal

import MyAPI.JDBC.MyTable

class MyDB(db: String) {
	enum class ERROR {
		SUCCESS,
		ERROR
	}

	private lateinit var connection: Connection
	private lateinit var statement: Statement
	private lateinit var resultSet: ResultSet

	public var tables: ArrayList<String> = ArrayList<String>()

	public var size: Int = 0
		get() = tables.size

	private var Error = ERROR.SUCCESS
	private var debug = false

	var fields: String = ""

	init {
		try {
			connection = DriverManager.getConnection("jdbc:sqlite:${db}")
			statement = connection.createStatement()

			loadTables()
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			e.printStackTrace()
		}
	}

	private fun loadTables() {
		dbg_msg("loadTables")
		try {
			val sql = "Select name From sqlite_master where type='table' order by name"
			resultSet = statement.executeQuery(sql)
			while (resultSet.next()) {
					tables.add(resultSet.getString(1))
			}
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			e.printStackTrace()
		}
	}

	fun createTable(lTable: String) {
		dbg_msg("create")
		try {
			var sql: String = "CREATE TABLE IF NOT EXISTS ${lTable} ( id INTEGER PRIMARY KEY NOT NULL "
			sql += if (fields.trim().isNotEmpty()) ", ${fields} )" else " )"
			statement.execute(sql)

			tables.add(lTable)
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

	// ## SQL			JDBC/Java					setXXX					updateXXX
	// #####################################################################################
	// # VARCHAR		java.lang.String			setString				updateString
	// # CHAR			java.lang.String			setString				updateString
	// # LONGVARCHAR	java.lang.String			setString				updateString
	// # BIT			boolean						setBoolean				updateBoolean
	// # NUMERIC		java.math.BigDecimal		setBigDecimal			updateBigDecimal
	// # TINYINT		byte						setByte					updateByte
	// # SMALLINT		short						setShort				updateShort
	// # INTEGER		int							setInt					updateInt
	// # BIGINT			long						setLong					updateLong
	// # REAL			float						setFloat				updateFloat
	// # FLOAT			float						setFloat				updateFloat
	// # DOUBLE			double						setDouble				updateDouble
	// # VARBINARY		byte[ ]						setBytes				updateBytes
	// # BINARY			byte[ ]						setBytes				updateBytes
	// # DATE			java.sql.Date				setDate					updateDate
	// # TIME			java.sql.Time				setTime					updateTime
	// # TIMESTAMP		java.sql.Timestamp			setTimestamp			updateTimestamp
	// # CLOB			java.sql.Clob				setClob					updateClob
	// # BLOB			java.sql.Blob				setBlob					updateBlob
	// # ARRAY			java.sql.Array				setARRAY				updateARRAY
	// # REF			java.sql.Ref				SetRef					updateRef
	// # STRUCT			java.sql.Struct				SetStruct				updateStruct

	operator fun get(lTable: String): MyTable {
		dbg_msg("getTable")

		// if (!(tables.contains(lTable)))
		createTable(lTable)

		var hmList = ArrayList<HashMap<String, Any>>()
		try {
			resultSet = statement.executeQuery("SELECT * FROM ${lTable}")
			while (resultSet.next()) {
				var hmColumn = HashMap<String, Any>()
				var md: ResultSetMetaData = resultSet.getMetaData()
				for (index in  1..md.getColumnCount()) {
					var cName = md.getColumnName(index)
					var cType  = md.getColumnType(index)

					hmColumn[cName] = when(cType) {
						// Types.ARRAY		-> resultSet.getARRAY(index)
						// Types.STRUCT		-> resultSet.getStruct(index)

						Types.VARCHAR		-> resultSet.getString(index)
						Types.CHAR			-> resultSet.getString(index)
						Types.LONGVARCHAR	-> resultSet.getString(index)

						Types.BIT			-> resultSet.getBoolean(index)
						Types.NUMERIC		-> resultSet.getBigDecimal(index)

						Types.TINYINT		-> resultSet.getByte(index)
						Types.SMALLINT		-> resultSet.getShort(index)
						Types.INTEGER		-> resultSet.getInt(index)
						Types.BIGINT		-> resultSet.getLong(index)

						Types.REAL			-> resultSet.getFloat(index)
						Types.FLOAT			-> resultSet.getFloat(index)
						Types.DOUBLE		-> resultSet.getDouble(index)

						Types.VARBINARY		-> resultSet.getBytes(index)
						Types.BINARY		-> resultSet.getBytes(index)

						Types.DATE			-> resultSet.getDate(index)

						Types.TIME			-> resultSet.getTime(index)
						Types.TIMESTAMP		-> resultSet.getTimestamp(index)

						Types.CLOB			-> resultSet.getClob(index)

						Types.BLOB			-> resultSet.getBlob(index)

						Types.REF			-> resultSet.getRef(index)

						else				-> dbg_msg("Type Not found to read from db")
					}
				}
				hmList.add(hmColumn)
			}
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			e.printStackTrace()
		}

		return MyTable(this, lTable, hmList)
	}

	fun updateMyTable(lTable: String, mTable: MyTable) {
		dbg_msg("updateMyTable")

		var hmList = ArrayList<HashMap<String, Any>>()
		try {
			resultSet = statement.executeQuery("SELECT * FROM ${lTable}")
			while (resultSet.next()) {
				var hmColumn = HashMap<String, Any>()
				var md: ResultSetMetaData = resultSet.getMetaData()
				for (index in  1..md.getColumnCount()) {
					var cName = md.getColumnName(index)
					var cType  = md.getColumnType(index)

					hmColumn[cName] = when(cType) {
						Types.VARCHAR		-> resultSet.getString(index)
						Types.CHAR			-> resultSet.getString(index)
						Types.LONGVARCHAR	-> resultSet.getString(index)

						Types.BIT			-> resultSet.getBoolean(index)
						Types.NUMERIC		-> resultSet.getBigDecimal(index)

						Types.TINYINT		-> resultSet.getByte(index)
						Types.SMALLINT		-> resultSet.getShort(index)
						Types.INTEGER		-> resultSet.getInt(index)
						Types.BIGINT		-> resultSet.getLong(index)

						Types.REAL			-> resultSet.getFloat(index)
						Types.FLOAT			-> resultSet.getFloat(index)
						Types.DOUBLE		-> resultSet.getDouble(index)

						Types.VARBINARY		-> resultSet.getBytes(index)
						Types.BINARY		-> resultSet.getBytes(index)

						Types.DATE			-> resultSet.getDate(index)

						Types.TIME			-> resultSet.getTime(index)
						Types.TIMESTAMP		-> resultSet.getTimestamp(index)

						Types.CLOB			-> resultSet.getClob(index)

						Types.BLOB			-> resultSet.getBlob(index)

						Types.REF			-> resultSet.getRef(index)

						else				-> dbg_msg("Type Not found to read from db")
					}
				}
				hmList.add(hmColumn)
			}
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			e.printStackTrace()
		}

		mTable.setTableData(hmList)
	}

	fun addColumn(lTable: String, column: String, default: Any) {
		dbg_msg("addColumn")

		var type = when(default) {
			is Boolean		-> " BIT"
			is Byte			-> " TINYINT"
			is Short		-> " SMALLINT"
			is Int			-> " INTEGER"
			is Long			-> " BIGINT"
			is Float		-> " FLOAT"
			is Double		-> " DOUBLE"
			// is Bytes		-> " "
			is BigDecimal	-> " NUMERIC"
			is Date			-> " DATE"
			is Time			-> " TIME"
			is Timestamp	-> " TIMESTAMP"
			is Clob			-> " CLOB"
			is Blob			-> " BLOB"
			is Ref			-> " REF"
			else			-> " TEXT"
		}

		try {
			var sql = "PRAGMA table_info ( ${lTable} )"
			val cName = column.split(" ")[0]
			var found = false

			dbg_msg(sql)

			resultSet = statement.executeQuery(sql)
			while (resultSet.next()) {
				// ID = 1, Column Name, Column Type, ... etc
				if (resultSet.getString(2) == cName) {
					found = true
				}
			}
			if (!found) {
				sql = "ALTER TABLE ${lTable} ADD COLUMN ${column} NOT NULL DEFAULT ${type}"
				statement.execute(sql)
			}
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			e.printStackTrace()
		}
	}

	fun dropColumn(lTable: String, column: String) {
		dbg_msg("dropColumn")
		try {
			var sql = "PRAGMA table_info ( ${lTable} )"
			dbg_msg(sql)

			resultSet = statement.executeQuery(sql)

			sql = "CREATE TABLE ${lTable}_backup AS SELECT id"
			while (resultSet.next()) {
				var key = resultSet.getString(2)

				dbg_msg(key)
				// ID = 1, Column Name, Column Type, ... etc
				// FIXME: id:1
				if (key == column || key == "id" || key == "id:1") continue

				sql += ", ${key}"
			}
			sql += " FROM ${lTable}"

			dbg_msg(sql)
			statement.execute(sql)
			statement.execute("DROP TABLE ${lTable}")
			statement.execute("ALTER TABLE ${lTable}_backup RENAME TO ${lTable}")
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			e.printStackTrace()
		}
	}

	fun addRow(lTable: String, hm: HashMap<String, Any>) {
		dbg_msg("addRow")
		var size = hm.size
		var fields = "INSERT INTO ${lTable} ( "
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
			dbg_msg(fields + values + size)
			var pstmt: PreparedStatement = connection.prepareStatement(fields + values)
			var index = 1
			for(key in hm.keys) {
				if (key != "id") {
					val item = hm[key]
					when(item) {
						is Boolean		-> pstmt.setBoolean(index++,	item)
						is Short		-> pstmt.setShort(index++,		item)
						is Int			-> pstmt.setInt(index++,		item)
						is Long			-> pstmt.setLong(index++,		item)
						is Float		-> pstmt.setFloat(index++,		item)
						is Double		-> pstmt.setDouble(index++,		item)
						is String		-> pstmt.setString(index++,		item)

						is Byte			-> pstmt.setByte(index++,		item)
						// is Bytes		-> pstmt.setBytes(index++,		item)

						is BigDecimal	-> pstmt.setBigDecimal(index++,	item)
						is Date			-> pstmt.setDate(index++,		item)
						is Time			-> pstmt.setTime(index++,		item)
						is Timestamp	-> pstmt.setTimestamp(index++,	item)
						is Clob			-> pstmt.setClob(index++,		item)
						is Blob			-> pstmt.setBlob(index++,		item)
						is Ref			-> pstmt.setRef(index++,		item)

						else			-> dbg_msg("Type Not found to insert into db")
					}
				}
			}
			pstmt.executeUpdate()
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			e.printStackTrace()
		}
	}

	fun updateRow(lTable: String, hm: HashMap<String, Any>) {
		dbg_msg("updateRow")
		var sql = "UPDATE ${lTable} SET "
		for(key in hm.keys) {
			if (key != "id") {
				sql += "${key} = ? "
			}
		}
		sql += "WHERE id = ?"
		dbg_msg(sql)

		try {
			var pstmt: PreparedStatement = connection.prepareStatement(sql)
			var index = 1
			for(key in hm.keys) {
				if (key != "id") {
					val item = hm[key]
					when(item) {
						is Boolean		-> pstmt.setBoolean(index++,	item)
						is Short		-> pstmt.setShort(index++,		item)
						is Int			-> pstmt.setInt(index++,		item)
						is Long			-> pstmt.setLong(index++,		item)
						is Float		-> pstmt.setFloat(index++,		item)
						is Double		-> pstmt.setDouble(index++,		item)
						is String		-> pstmt.setString(index++,		item)

						is Byte			-> pstmt.setByte(index++,		item)
						// is Bytes		-> pstmt.setBytes(index++,		item)

						is BigDecimal	-> pstmt.setBigDecimal(index++,	item)
						is Date			-> pstmt.setDate(index++,		item)
						is Time			-> pstmt.setTime(index++,		item)
						is Timestamp	-> pstmt.setTimestamp(index++,	item)
						is Clob			-> pstmt.setClob(index++,		item)
						is Blob			-> pstmt.setBlob(index++,		item)
						is Ref			-> pstmt.setRef(index++,		item)

						else			-> dbg_msg("Type Not found to insert into db")
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

	fun dropRow(lTable: String, lId: Int) {
		dbg_msg("dropRow")
		var sql = "DELETE FROM ${lTable} WHERE id = ?"
		dbg_msg(sql)
		try {
			var pstmt: PreparedStatement = connection.prepareStatement(sql)
			pstmt.setInt(1, lId)
			pstmt.execute()
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			e.printStackTrace()
		}
	}

	fun dropTable(lTable: String) {
		dbg_msg("dropTable")
		try {
			val sql = "DROP TABLE IF EXISTS ${lTable}"
			statement.execute(sql)
			loadTables()
		} catch (e: SQLException) {
			Error = ERROR.ERROR
			e.printStackTrace()
		}
	}

	fun dbg_msg(msg: String) {
		if (debug)
			println("MyDB: " + msg)
	}

	fun enableDBG() {
		dbg_msg("enableDBG")
		debug = true
	}

	fun disableDBG() {
		dbg_msg("disableDBG")
		debug = false
	}

	protected fun finalize() {
		dbg_msg("finalize")
		try	{
			resultSet.close()
			statement.close()
			connection.close()
		} catch (e: Exception) {
			Error = ERROR.ERROR
			e.printStackTrace()
		}
	}

	fun query(lTable: String, hm: HashMap<String, Any>): ArrayList<HashMap<String, Any>> {
		dbg_msg("query")
		var hmList = ArrayList<HashMap<String, Any>>()

		var sql = "SELECT id"
		for(key in hm.keys) {
			if (key != "id") {
				sql += ", " + key
			}
		}
		sql += " FROM ${lTable}"
		dbg_msg(sql)

		try {
			resultSet = statement.executeQuery(sql)
			while (resultSet.next()) {
				var hmColumn = HashMap<String, Any>()
				var md: ResultSetMetaData = resultSet.getMetaData()
				for (index in  1..md.getColumnCount()) {
					var cName = md.getColumnName(index)
					var cType  = md.getColumnType(index)

					hmColumn[cName] = when(cType) {
						Types.VARCHAR		-> resultSet.getString(index)
						Types.CHAR			-> resultSet.getString(index)
						Types.LONGVARCHAR	-> resultSet.getString(index)

						Types.BIT			-> resultSet.getBoolean(index)
						Types.NUMERIC		-> resultSet.getBigDecimal(index)

						Types.TINYINT		-> resultSet.getByte(index)
						Types.SMALLINT		-> resultSet.getShort(index)
						Types.INTEGER		-> resultSet.getInt(index)
						Types.BIGINT		-> resultSet.getLong(index)

						Types.REAL			-> resultSet.getFloat(index)
						Types.FLOAT			-> resultSet.getFloat(index)
						Types.DOUBLE		-> resultSet.getDouble(index)

						Types.VARBINARY		-> resultSet.getBytes(index)
						Types.BINARY		-> resultSet.getBytes(index)

						Types.DATE			-> resultSet.getDate(index)

						Types.TIME			-> resultSet.getTime(index)
						Types.TIMESTAMP		-> resultSet.getTimestamp(index)

						Types.CLOB			-> resultSet.getClob(index)

						Types.BLOB			-> resultSet.getBlob(index)

						Types.REF			-> resultSet.getRef(index)

						else				-> dbg_msg("Type Not found to read from db")
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
			dbg_msg("Row: ${rowOut}")
		}

		return hmList
	}

	fun classFromType(type: Int): String {
		dbg_msg("classFromType")
		return when(type) {
			Types.ARRAY			-> "ARRAY"
			Types.STRUCT		-> "Struct"
			Types.VARCHAR		-> "String"
			Types.CHAR			-> "String"
			Types.LONGVARCHAR	-> "String"
			Types.BIT			-> "Boolean"
			Types.NUMERIC		-> "BigDecimal"
			Types.TINYINT		-> "Byte"
			Types.SMALLINT		-> "Short"
			Types.INTEGER		-> "Int"
			Types.BIGINT		-> "Long"
			Types.REAL			-> "Float"
			Types.FLOAT			-> "Float"
			Types.DOUBLE		-> "Double"
			Types.VARBINARY		-> "Bytes"
			Types.BINARY		-> "Bytes"
			Types.DATE			-> "Date"
			Types.TIME			-> "Time"
			Types.TIMESTAMP		-> "Timestamp"
			Types.CLOB			-> "Clob"
			Types.BLOB			-> "Blob"
			Types.REF			-> "Ref"
			else				-> ""
		}
	}

	fun drop() {
	}
}