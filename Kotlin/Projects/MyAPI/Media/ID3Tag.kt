package MyAPI.Media

import java.io.File
import java.io.FileInputStream

//  Field      Length    Offsets
//  Tag        3           0-2
//  Songname   30          3-32
//  Artist     30         33-62
//  Album      30         63-92
//  Year       4          93-96
//  Comment    30         97-126
//  Genre      1           127

class ID3Tag(file: String) {
	var Tag     : String = ""
	var Title   : String = ""
	var Artist  : String = ""
	var Album   : String = ""
	var Year    : String = ""
	var Comment : String = ""
	var Genre   : String = ""

	init {
		try {
			var sFile = File(file)
			var song  = FileInputStream(sFile)
			var last128 = ByteArray(128)

			song.skip(sFile.length() - 128)
			song.read(last128)

			var id3 = String(last128)
			Tag = id3.substring(0, 3)
			if (Tag.equals("TAG")) {
				Title    = id3.substring( 3, 32)
				Artist   = id3.substring(33, 62)
				Album    = id3.substring(63, 92)
				Year     = id3.substring(93, 96)
				Comment  = id3.substring(97, 126)
				Genre    = id3.substring(127)
			}
		} catch (e: Exception) {
			println(e)
		}
	}

	override fun toString(): String {
		return ("Tag     : $Tag\n"
			 + "Title   : $Title\n"
			 + "Artist  : $Artist\n"
			 + "Album   : $Album\n"
			 + "Year    : $Year\n"
			 + "Comment : $Comment\n"
			 + "Genre   : $Genre")
	}
}