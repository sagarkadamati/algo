package MyAPI.FileManager

import kotlin.io

class MyPath(str: String) {
	private var path: String = ""

	companion object {
		public val RECURSIVE: Boolean = true
	}

	init {
		set(str)
	}

	fun get() : String {
		return this.path
	}

	fun set(pathStr: String) {
		this.path = pathStr
	}

	fun backward() {

	}

	fun forward(dir: String) {
		this.path += '\\' + dir
	}

	fun fixPath() {

	}

	fun getFiles(recursive: Boolean = false) {
		if (!recursive) {
			File(this.path)
			.walkTopDown()
			.maxDepth(1)
			.forEach {
				println(it)
			}
		}
		else {
			File(this.path)
			.walkTopDown()
			.forEach {
				println(it)
			}
		}
	}
}