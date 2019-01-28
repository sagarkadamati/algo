package MyAPI.FileManager

import java.io.File

class MyFile() {
	enum class Type {
		DIRECTORY,
		TEXT,
		IMAGE,
		VIDEO,
		AUDIO,
		UNKNOWN
	}

	companion object {
		private var myFile: File = File("/")
	}

	val name: String get() = myFile.nameWithoutExtension
	val fullName: String get() = myFile.name
	var location: String
		get() = myFile.absolutePath
		set(newLocation: String) {
			myFile = File(File(newLocation).absolutePath)
		}
	val type: String get() = myFile.extension
	val size: Long get() = myFile.length()
	val modifiedOn: Long get() = myFile.lastModified()

	constructor (str: String): this() {
		location = str
	}

	private fun iType(): String {
		return myFile.extension

		// if (myFile.isDirectory) {
		// 	return Type.DIRECTORY
		// } else {
		// 	return Type.UNKNOWN
		// }
	}

	infix fun move(newName: String) {
		if (myFile.renameTo(File(newName)))
			myFile = File(newName)
	}

	infix fun goto(name: String) {
		if (myFile.isDirectory()) {
			myFile = File(myFile.getAbsolutePath() + "/${name}")
		}
	}

	fun goBack() {
		var f = location.split("[/|\\\\]".toRegex())
		if (f.count() > 1) {
			if (!f[1].isNullOrEmpty()) {
				myFile = myFile.getParentFile()
			}
		}
	}

	fun freeSpace(): Long {
		return myFile.getFreeSpace()
	}

	fun list(value: Int = Int.MAX_VALUE): Sequence<File> {
		return myFile.walkTopDown().maxDepth(value)
	}

	fun listAudios(value: Int = Int.MAX_VALUE): Sequence<File> {
		return myFile.walkTopDown().maxDepth(value).filter { it.isFile && it.extension.equals("mp3", ignoreCase = true) }
	}

	fun listVideos(value: Int = Int.MAX_VALUE): Sequence<File> {
		return myFile.walkTopDown().maxDepth(value).filter { it.isFile && it.extension.equals("mp4", ignoreCase = true) }
	}

	fun listImages(value: Int = Int.MAX_VALUE): Sequence<File> {
		return myFile.walkTopDown().maxDepth(value).filter { it.isFile && it.extension.equals("jpg", ignoreCase = true) }
	}

	fun ls() {
		list(1).forEach {
			println(it)
		}
	}

	override fun toString(): String {
		return "${fullName}"
	}

    // fun getTitle() { path.getFileSongTitle() }

    // fun getGenre() { path.getFileGenre() }

    // fun getAlbum() { path.getFileAlbum() }

    // fun getArtist() { path.getFileArtist() }

    // fun getDuration() { path.getDuration() }

    // fun getResolution() { path.getResolution() }
}
	// he file denoted by this abstract pathname.
	// boolean canExecute()			: Tests whether the applicat
	// boolean canRead() 			: Tests whether the application can read the file denoted by this abstract pathname.
	// boolean canWrite() 			: Tests whether the application can modify the file denoted by this abstract pathname.
	// int compareTo(File pathname) : Compares two abstract pathnames lexicographically.
	// boolean createNewFile()		: Atomically creates a new, empty file named by this abstract pathname .
	// static File createTempFile(String prefix, String suffix) : Creates an empty file in the default temporary-file directory.
	// boolean delete()				: Deletes the file or directory denoted by this abstract pathname.
	// boolean equals(Object obj)	: Tests this abstract pathname for equality with the given object.
	// boolean exists()				: Tests whether the file or directory denoted by this abstract pathname exists.
	// String getAbsolutePath() 	: Returns the absolute pathname string of this abstract pathname.
	// long getFreeSpace()			: Returns the number of unallocated bytes in the partition .
	// String getName()				: Returns the name of the file or directory denoted by this abstract pathname.
	// String getParent()			: Returns the pathname string of this abstract pathname’s parent.
	// File getParentFile()			: Returns the abstract pathname of this abstract pathname’s parent.
	// String getPath()				: Converts this abstract pathname into a pathname string.
	// boolean isDirectory()		: Tests whether the file denoted by this pathname is a directory.
	// boolean isFile()				: Tests whether the file denoted by this abstract pathname is a normal file.
	// boolean isHidden()			: Tests whether the file named by this abstract pathname is a hidden file.
	// long length()				: Returns the length of the file denoted by this abstract pathname.
	// String[] list()				: Returns an array of strings naming the files and directories in the directory .
	// File[] listFiles()			: Returns an array of abstract pathnames denoting the files in the directory.
	// boolean mkdir()				: Creates the directory named by this abstract pathname.
	// boolean renameTo(File dest) 	: Renames the file denoted by this abstract pathname.
	// boolean setExecutable(boolean executable) : A convenience method to set the owner’s execute permission.
	// boolean setReadable(boolean readable) : A convenience method to set the owner’s read permission.
	// boolean setReadable(boolean readable, boolean ownerOnly) : Sets the owner’s or everybody’s read permission.
	// boolean setReadOnly()		: Marks the file or directory named so that only read operations are allowed.
	// boolean setWritable(boolean writable) : A convenience method to set the owner’s write permission.
	// String toString()			: Returns the pathname string of this abstract pathname.
	// URI toURI()					: Constructs a file URI that represents this abstract pathname.


// fun File.getDirectChildrenCount(countHiddenItems: Boolean) = listFiles()?.filter { if (countHiddenItems) true else !it.isHidden }?.size ?: 0

// fun File.toFileDirItem(context: Context) = FileDirItem(absolutePath, name, context.getIsPathDirectory(absolutePath), 0, length())
// package com.simplemobiletools.commons.models

// import android.content.Context
// import com.simplemobiletools.commons.extensions.*
// import com.simplemobiletools.commons.helpers.*
// import java.io.File

// data class FileDirItem(val path: String, val name: String = "", var isDirectory: Boolean = false, var children: Int = 0, var size: Long = 0L) :
//         Comparable<FileDirItem> {
//     companion object {
//         var sorting: Int = 0
//     }

//     override fun compareTo(other: FileDirItem): Int {
//         return if (isDirectory && !other.isDirectory) {
//             -1
//         } else if (!isDirectory && other.isDirectory) {
//             1
//         } else {
//             var result: Int
//             when {
//                 sorting and SORT_BY_NAME != 0 -> result = name.toLowerCase().compareTo(other.name.toLowerCase())
//                 sorting and SORT_BY_SIZE != 0 -> result = when {
//                     size == other.size -> 0
//                     size > other.size -> 1
//                     else -> -1
//                 }
//                 sorting and SORT_BY_DATE_MODIFIED != 0 -> {
//                     val file = File(path)
//                     val otherFile = File(other.path)
//                     result = when {
//                         file.lastModified() == otherFile.lastModified() -> 0
//                         file.lastModified() > otherFile.lastModified() -> 1
//                         else -> -1
//                     }
//                 }
//                 else -> {
//                     result = getExtension().toLowerCase().compareTo(other.getExtension().toLowerCase())
//                 }
//             }

//             if (sorting and SORT_DESCENDING != 0) {
//                 result *= -1
//             }
//             result
//         }
//     }

//     fun getExtension() = if (isDirectory) name else path.substringAfterLast('.', "")

//     fun getBubbleText() = when {
//         sorting and SORT_BY_SIZE != 0 -> size.formatSize()
//         sorting and SORT_BY_DATE_MODIFIED != 0 -> File(path).lastModified().formatDate()
//         sorting and SORT_BY_EXTENSION != 0 -> getExtension().toLowerCase()
//         else -> name
//     }

//     fun getProperSize(context: Context, countHidden: Boolean): Long {
//         return if (path.startsWith(OTG_PATH)) {
//             context.getDocumentFile(path)?.getItemSize(countHidden) ?: 0
//         } else {
//             File(path).getProperSize(countHidden)
//         }
//     }

//     fun getProperFileCount(context: Context, countHidden: Boolean): Int {
//         return if (path.startsWith(OTG_PATH)) {
//             context.getDocumentFile(path)?.getFileCount(countHidden) ?: 0
//         } else {
//             File(path).getFileCount(countHidden)
//         }
//     }

//     fun getDirectChildrenCount(context: Context, countHiddenItems: Boolean): Int {
//         return if (path.startsWith(OTG_PATH)) {
//             context.getDocumentFile(path)?.listFiles()?.filter { if (countHiddenItems) true else !it.name.startsWith(".") }?.size ?: 0
//         } else {
//             File(path).getDirectChildrenCount(countHiddenItems)
//         }
//     }

//     fun getLastModified(context: Context): Long {
//         return if (path.startsWith(OTG_PATH)) {
//             context.getFastDocumentFile(path)?.lastModified() ?: 0L
//         } else {
//             File(path).lastModified()
//         }
//     }

//     fun getParentPath() = path.getParentPath()

//     fun getDuration() = path.getDuration()

//     fun getFileDurationSeconds() = path.getFileDurationSeconds()

//     fun getArtist() = path.getFileArtist()

//     fun getAlbum() = path.getFileAlbum()

//     fun getSongTitle() = path.getFileSongTitle()

//     fun getResolution() = path.getResolution()

//     fun getVideoResolution() = path.getVideoResolution()

//     fun getImageResolution() = path.getImageResolution()

//     fun getPublicUri(context: Context) = context.getDocumentFile(path)?.uri ?: ""
// }