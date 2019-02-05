package MyAPI.Extensions

import java.io.File
import java.io.IOException
import java.util.concurrent.TimeUnit

fun String.runCommand(workingDir: File = File("."),
	timeoutAmount: Long = 60,
	timeoutUnit: TimeUnit = TimeUnit.SECONDS): String {

	return try {
		ProcessBuilder(*this.split("\\s".toRegex()).toTypedArray())
			.directory(workingDir)
			.redirectOutput(ProcessBuilder.Redirect.PIPE)
			.redirectError(ProcessBuilder.Redirect.PIPE)
			.start().apply {
				waitFor(timeoutAmount, timeoutUnit)
			}
			.inputStream.bufferedReader().readText()
	} catch (e: IOException) {
		e.printStackTrace()
		""
	}
}

fun String.readLines(): List<String> {
	return try {
		File(this).readLines()
	} catch (e: IOException) {
		e.printStackTrace()
		listOf("")
	}
}

fun String.readText(): String {
	return try {
		File(this).readText()
	} catch (e: IOException) {
		e.printStackTrace()
		""
	}
}