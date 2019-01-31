package MyAPI.JDBC

import java.sql.Connection
import java.sql.DriverManager
import java.sql.ResultSet
import java.sql.Statement
import java.sql.DatabaseMetaData
import java.sql.SQLException
import java.sql.PreparedStatement

class MyDB(db: String) {
	private var conn: Connection ?= null
	private var statement: Statement ?= null
	private var resultSet: ResultSet ?= null

	var table: String = ""

	init {
		try {
			conn = DriverManager.getConnection("jdbc:sqlite:${db}")
			statement = conn!!.createStatement()
		} catch (e: SQLException) {
			println(e)
		}
	}

	fun query(q: String) {
		try {
			resultSet = statement!!.executeQuery(q)
		} catch (e: SQLException) {
			println(e)
		}
	}

	fun close() {
		try	{
			if (resultSet != null)
				resultSet!!.close()

			if (statement != null)
				statement!!.close()

			if (conn != null)
				conn!!.close()
		} catch (e: Exception) {
			e.printStackTrace()
		}
	}

	fun create(fields: String) {
		var sql: String = "CREATE TABLE IF NOT EXISTS ${table} ( ${fields} )"
		query(sql)

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

	fun insert(name: String, capacity: Double) {
		var sql: String = "INSERT INTO ${table} (name, capacity) VALUES(?,?)"

		try {
			var pstmt: PreparedStatement = conn!!.prepareStatement(sql)

			pstmt.setString(1, name)
			pstmt.setDouble(2, capacity)
			pstmt.executeUpdate()
		} catch (e: SQLException) {
			println(e)
		}
	}

	fun selectAll(fields: String){
		query("SELECT ${fields} FROM ${table}")

		// try {
		// 	// loop through the result set
		// 	while (rs.next()) {
		// 		System.out.println(rs.getInt("id") +"\t" +
	 	// 		rs.getString("name") + "\t" +
	 	// 		rs.getDouble("capacity"))
		// 	}
		// } catch (e: SQLException) {
		// 	println(e)
		// }
	}

	fun update(id: Int, name: String, capacity: Double) {
		var sql: String = "UPDATE ${table} SET name = ? , capacity = ? WHERE id = ?"

		try {
			var pstmt: PreparedStatement = conn!!.prepareStatement(sql)

			// set the corresponding param
			pstmt.setString(1, name)
			pstmt.setDouble(2, capacity)
			pstmt.setInt(3, id)

			// update
			pstmt.executeUpdate()
		} catch (e: SQLException) {
			println(e)
		}
	}

	fun delete(fields: String) {
		var sql: String = "DELETE TABLE IF EXISTS ${table} ( ${fields} )"
		query(sql)
	}

	fun deleteRow(id: Int) {
		var sql: String = "DELETE FROM ${table} WHERE id = ?"

		try {
			var pstmt: PreparedStatement = conn!!.prepareStatement(sql)

			// set the corresponding param
			pstmt.setInt(1, id)
			// execute the delete statement
			pstmt.executeUpdate()

		} catch (e: SQLException) {
			println(e)
		}
	}

	fun connect(db: String) {
		var conn: Connection = DriverManager.getConnection(db)
		try {
			var meta: DatabaseMetaData = conn.getMetaData()
			println("The driver name is " + meta.getDriverName())
			println("A new database has been created.")
		} catch (e: SQLException) {
			println(e)
		}
	}

	fun connecto() {
		try {
			// Class.forName("org.sqlite.JDBC")
			conn = DriverManager.getConnection("jdbc:sqlite:C:/Users/Sagar/Workspace/test.db")
			statement = conn!!.createStatement()
			resultSet = statement!!.executeQuery("SELECT EMPNAME FROM EMPLOYEEDETAILS")

			while (resultSet!!.next()) {
				println("EMPLOYEE NAME:" + resultSet!!.getString("EMPNAME"))
			}
		}
		catch (e: Exception)
		{
			e.printStackTrace()
		}
		finally
		{
			close()
		}
 	}
}