package MyAPI.FileManager

import java.io.File

class MyFolder(str: String) {
	companion object {
		public val RECURSIVE: Boolean = true
	}

	private var fname = ""
	private var file: File ?= null

	val name: String get() = this.fname

	init {
		this.fname = str
	}

	fun listFiles(recursive: Boolean = false) {
		if (!recursive) {
			File(this.fname)
			.walkTopDown()
			.maxDepth(1)
			.forEach {
				println(it)
			}
		}
		else {
			File(this.fname)
			.walkTopDown()
			.forEach {
				println(it)
			}
		}
	}

	fun listFolders(recursive: Boolean = false) {
		if (!recursive) {
			File(this.fname)
			.walkTopDown()
			.maxDepth(1)
			.forEach {
				println(it)
			}
		}
		else {
			File(this.fname)
			.walkTopDown()
			.forEach {
				println(it)
			}
		}
	}
}