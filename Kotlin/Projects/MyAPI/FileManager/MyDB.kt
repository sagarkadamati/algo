package MyAPI.FileManager

import java.sql.Connection
import java.sql.DriverManager
import java.sql.ResultSet
import java.sql.Statement
import java.sql.DatabaseMetaData
import java.sql.SQLException

class MyDB {
	var connection: Connection ?= null
	var resultSet: ResultSet ?= null
	var statement: Statement ?= null

	init {
		create()
	}

	fun create() {
		var conn: Connection = DriverManager.getConnection("jdbc:sqlite:C:/Users/Sagar/Workspace/test.db")
		try {
			var meta: DatabaseMetaData = conn.getMetaData()
			println("The driver name is " + meta.getDriverName())
			println("A new database has been created.")
		} catch (e: SQLException) {
			println(e)
		}
	}

	 fun connect() {
		try {
			Class.forName("org.sqlite.JDBC")
			connection = DriverManager.getConnection("jdbc:sqlite:C:/Users/Sagar/Workspace/test.db")
			statement = connection!!.createStatement()
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
			try
			{
				resultSet!!.close()
				statement!!.close()
				connection!!.close()
			}
			catch (e: Exception)
			{
				e.printStackTrace()
			}
		}
 	 }
}