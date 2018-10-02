function Get-MovieURLs($URLLink) {
	$Response = Invoke-WebRequest -UseBasicParsing -Uri $URLLink

	$Urls = ($Response.Links | Where-Object {$_.href -like "*flac*download.html"}).href | Get-Unique

	return $Urls
}

function Get-PageCount($Page) {
	$Response = Invoke-WebRequest -UseBasicParsing -Uri $Page
	$Pages  = $Response.Links | Where-Object {$_.href -like "*page*"}

	$Count = $Pages[-1].innerText

	if ($Count -like "*Next*")
	{
		$Count = $Pages[-2].innerText
	}

	return $Count
}

function Audio($BaseURL)
{
	$MovieUrls = @()
	$PageCount = Get-PageCount $($BaseURL + "/page/1")

	foreach ($PageNo in 1..$PageCount) {
		$URL = $BaseURL + "/page/" + $PageNo
		Get-MovieURLs $URL
	}
}

function Update-ID3($AudioFile, $Artist) {
	if ($AudioFile) {
		$File  = (Get-ChildItem $AudioFile)
		$Title = ($File.BaseName -split $([regex]::Match($File.BaseName, '(^[0-9]*[ ]*)').Groups[0].Value))[1]
		$Album = ((Get-Location).Path -split [regex]::Escape([IO.Path]::DirectorySeparatorChar))[-1]
		$Genre = "$Album`: $($($File.Directory).Name)"
		$Track = ($File.BaseName -split " ")[0]

		$Album = "Bhagavatam Samhita: "
		$Album += ((Get-Location).Path -split [regex]::Escape([IO.Path]::DirectorySeparatorChar))[-1]
		$Genre = "$Album"

		if (Test-Path $(Join-Path $(($File.Directory).Name) "cover.*"))
		{
			$COVER = Join-Path $(($File.Directory).Name) $(Get-ChildItem -Name -File -Filter "cover.*" -Path ($File.Directory).Name)
		}
		else
		{
			if (Test-Path "cover.*")
			{
				$COVER = Get-ChildItem -Name -File -Filter "cover.*" -Path .
			}
		}

		# $MID3V2 = [System.IO.Path]::Combine($ToolsLocation, "Python", "Scripts", "mid3v2")
		# python $MID3V2 -d "$AudioFile"

		# $COVER = Get-ChildItem -Name -File -Filter "cover.*" -Path .
		$EYED3 = [System.IO.Path]::Combine($ToolsLocation, "Python", "Scripts", "eyeD3.exe")

		if ($COVER) {
			$COVER += ":FRONT_COVER"
			if ($Artist) {
				& $EYED3 --to-v2.4 --add-image $COVER --album-artist $Album --artist $Artist --album $Album --title $Title --genre $Genre --non-std-genres --track $Track $AudioFile
			}
			else {
				& $EYED3 --to-v2.4 --add-image $COVER  --album-artist $Album --album $Album --title $Title --genre $Genre --non-std-genres --track $Track $AudioFile
			}
		}
		else {
			if ($Artist) {
				& $EYED3 --to-v2.4 --album-artist $Album --artist $Artist --album $Album --title $Title --genre $Genre --non-std-genres --track $Track $AudioFile
			}
			else {
				& $EYED3 --to-v2.4  --album-artist $Album --album $Album --title $Title --genre $Genre --non-std-genres --track $Track $AudioFile
			}
		}

		# $MID3V2 = [System.IO.Path]::Combine($ToolsLocation, "Python", "Scripts", "mid3v2")
		# python $MID3V2 -d --artist="$Artist" --album="$Album" --song="$Title" --genre="$Genre" --track="$Track" "$AudioFile"
	}
}

function Update-ID3Files {
	param (
		[String]$Artist
	)

	$Files  = Get-FileNames -Recursive "mp3"
	$Files += Get-FileNames -Recursive "flac"

	foreach ($File in $Files) {
		Update-ID3 "$File" "$Artist"
	}
}

function Get-Parvam($URL) {
	$response = Invoke-WebRequest -UseBasicParsing -Uri $URL
	$Links = ($response.Links).href | Select-String -Pattern "mp3$" | Get-Unique

	foreach ($link in $Links) {
		if ($link) {
			$FileName = $(Split-Path $link -Leaf)
			$SplitFileName = $FileName.split('_')

			$Track = ($SplitFileName[0] -replace 'MahaBharatam',' ').split(' ')[0]
			$Parvam = "Vana Parvam"
			$Title = "Bharatamlo Ramayanam.mp3"

			if ($FileName -notlike "*Ramayanam*") {
				$Parvam = StringSplitCaps $(($SplitFileName[0] -replace 'MahaBharatam',' ').split(' ')[1])
				$Title = $SplitFileName[1]

				if ($SplitFileName.Length -gt 2) {
					foreach ($i in 2..($SplitFileName.Length - 1)) {
						$Title += ", "
						$Title += $SplitFileName[$i]
					}
				}
			}

			$NewFileName = $(StringSplitCaps $($Track + " " + $Title))

			New-Item -Type Directory -Force $Parvam | Out-Null

			# Write-Output "Invoke-WebRequest -UseBasicParsing -Uri $link -OutFile $(Join-Path $Parvam $NewFileName)"
			$FileName = $(Join-Path $Parvam $NewFileName)
			if (!$(Test-Path $FileName)) {
				Get-RemoteFile $link.Line $FileName
			}
		}
	}
}

function Get-Bharatam {
	New-Item -Type Directory "Maha Bharatam" | Out-Null
	Set-Location "Maha Bharatam"

	$BASEURL = "http://www.srichalapathirao.com/discourses?category=mahabharatam_"
	$PARVALU = (
		"adiparvam",
		"sabhaparvam",
		"vanaparvam",
		"virataparvam",
		"udyogaparvam"
		)

	foreach ($PARVAM in $PARVALU) {
		$URL = $BASEURL + $PARVAM
		Get-Parvam $URL
	}

	Copy-Item $([IO.Path]::Combine($ToolsLocation, "Env", "Album Arts", "Maha Baratam.jpg")) cover.jpg
	Update-ID3Files "Sri Chalapathi Rao"
	if (Test-Path "cover.jpg")
	{
		Remove-Item "cover.jpg" -ErrorAction Ignore
	}

	Set-Location ..
}

function Get-RemoteFile($URL, $FileName) {
	if (!$FileName) {
		$FileName = $(Split-Path $URL -Leaf)
	}

	try {
		Invoke-WebRequest -UseBasicParsing -Uri $URL -OutFile $FileName
	}
	catch {
		Write-Host "Missing: $URL"
	}
}

function Get-DasamaSkandam {
	New-Item -Type Directory -Force "Dasama Skandam" | Out-Null
	Set-Location "Dasama Skandam"

	$request = Invoke-WebRequest -UseBasicParsing -Uri "http://www.srichalapathirao.com/discourses?category=bhakti_dasama"
	$URLS = ($request.Links).href | Select-String "mp3" | Get-Unique

	foreach ($URL in $URLS) {
		$File = $(Split-Path $URL -Leaf)
		$FileName = $(StringSplitCaps $($File -replace "MP3", "mp3"))

		if (!$(Test-Path $FileName)) {
			Get-RemoteFile $URL.Line $FileName
		}
	}

	Move-Item -Force "01 Bhagavatam10.mp3" "01 Introduction.mp3"
	Move-Item -Force "26 Bhagavatam01.mp3" "26 Songs.mp3"
	Move-Item -Force "27 Bhagavatam02.mp3" "27 Songs.mp3"
	Move-Item -Force "28 Bhagavatam03.mp3" "28 Songs.mp3"

	Set-Location ..
}

function Get-Bhagavatam {
	New-Item -Type Directory -Force "Bhagavatam" | Out-Null
	Set-Location "Bhagavatam"

	Get-DasamaSkandam

	Copy-Item $([IO.Path]::Combine($ToolsLocation, "Env", "Album Arts", "Dasama Skandam.jpg")) cover.jpg
	Update-ID3Files "Sri Chalapathi Rao"
	if (Test-Path "cover.jpg")
	{
		Remove-Item "cover.jpg" -ErrorAction Ignore
	}

	Set-Location ..
}

function Get-BhagavadGeeta {

}

function Get-Capalized($String) {
	$TextInfo = (Get-Culture).TextInfo
	$TextInfo.ToTitleCase($String)
}

function Get-OldFixedFileName($tmp, $main, $sub) {
	$FileName = Split-Path $tmp -Leaf
	$FileName = $FileName -replace "MP3", "mp3"
	$FileName = StringSplitCaps $FileName

	$FileName = $FileName -replace "Adi Parvam_", ""
	$FileName = $FileName -replace "Virata Parvam_", ""
	$FileName = $FileName -replace "Sabha Parvam_", ""
	$FileName = $FileName -replace "Vana Parvam_", ""
	$FileName = $FileName -replace "Virata Parvam_", ""
	$FileName = $FileName -replace "Udyoga Parvam_", ""
	$FileName = $FileName -replace "Bheeshma Parvam_", ""
	$FileName = $FileName -replace "Maha Bharatam", ""

	if ($FileName -like "*_*") {
		$FileName = $FileName -replace $($main + "_"), ""
		$FileName = $FileName -replace $($main + ""), ""
		$FileName = $FileName -replace $($sub + "_"), ""
		$FileName = $FileName -replace $($sub + ""), ""
		$FileName = $FileName -replace "_ ", ","
	}

	$FileName = $FileName -replace "by", ""
	$FileName = $FileName -replace "sri", ""
	$FileName = $FileName -replace "chalapathi", ""
	$FileName = $FileName -replace "rao", ""

	$FileName = $FileName -replace "  ", ""
	$FileName = $FileName -replace "  ", ""
	$FileName = $FileName -replace "  ", ""
	$FileName = $FileName -replace "  ", ""

	$FileName = $FileName -replace " \.", "."

	$FileName = $FileName -replace "01 Bhagavatam10.mp3", "01 Introduction.mp3"
	$FileName = $FileName -replace "26 Bhagavatam01.mp3", "26 Songs.mp3"
	$FileName = $FileName -replace "27 Bhagavatam02.mp3", "27 Songs.mp3"
	$FileName = $FileName -replace "28 Bhagavatam03.mp3", "28 Songs.mp3"

	$FileName.Trim()
}

function Get-FixedFileName($tmp, $main, $sub) {
	$FileName = Split-Path $tmp -Leaf
	$FileName = $FileName -replace "MP3", "mp3"
	$FileName = StringSplitCaps $FileName

	$FileName = $FileName -replace "Adi Parvam_", ""
	$FileName = $FileName -replace "Virata Parvam_", ""
	$FileName = $FileName -replace "Sabha Parvam_", ""
	$FileName = $FileName -replace "Vana Parvam_", ""
	$FileName = $FileName -replace "Virata Parvam_", ""
	$FileName = $FileName -replace "Udyoga Parvam_", ""
	$FileName = $FileName -replace "Bheeshma Parvam_", ""
	$FileName = $FileName -replace "Maha Bharatam", ""
	$FileName = $FileName -replace " LO ", ""

	if ($FileName -like "*_*") {
		$FileName = $FileName -replace $($main + "_"), ""
		$FileName = $FileName -replace $($main + ""), ""
		$FileName = $FileName -replace $($sub + "_"), ""
		$FileName = $FileName -replace $($sub + ""), ""
		$FileName = $FileName -replace "_ ", ", "
	}

	$FileName = $FileName -replace "by", ""
	$FileName = $FileName -replace "sri", ""
	$FileName = $FileName -replace "chalapathi", ""
	$FileName = $FileName -replace "rao", ""

	$FileName = $FileName -replace "  ", " "
	$FileName = $FileName -replace "  ", " "
	$FileName = $FileName -replace "  ", " "
	$FileName = $FileName -replace "  ", " "

	$FileName = $FileName -replace " \.", "."

	$FileName = $FileName -replace "01 Bhagavatam10.mp3", "01 Introduction.mp3"
	$FileName = $FileName -replace "26 Bhagavatam01.mp3", "26 Songs.mp3"
	$FileName = $FileName -replace "27 Bhagavatam02.mp3", "27 Songs.mp3"
	$FileName = $FileName -replace "28 Bhagavatam03.mp3", "28 Songs.mp3"

	$FileName.Trim()
}

function Get-AlternateName($FileName) {
	switch ($FileName) {
		"Sanskrit Bharatam" { "Maha Bharatam" }
		"Brahmasutras" { "Brahma Sutras" }
		"Gita" { "Bhagavad Geeta" }
		"Prakaranas" { "Prakaranalu" }
		Default { $FileName }
	}
}

function Get-SriChalapathiRaoAudio {
	$Vedanta = ([IO.Path]::Combine($HOME, "Music", "Vedanta", "Sri Chalapathi Rao"))
	New-Item -Type Directory -Force $Vedanta | Out-Null

	[Net.ServicePointManager]::SecurityProtocol = "tls12, tls11, tls"
	$response = Invoke-WebRequest -UseBasicParsing -Uri http://www.srichalapathirao.com/discourses
	$links = ($response.Links | Where-Object href -Like "*subject=*").href

	foreach ($link in $links) {
		$Category  = ([regex]::Match($link, '(category=)([a-z]|[A-Z]|[0-9])*(_)([a-z]|[A-Z]|[0-9])*')).Value -replace "category=", ""
		$Group     = Get-Capalized $(([regex]::Match($Category, '([a-z]|[A-Z]|[0-9])*_')).Value -replace "_", "")

		$Subject    = (([regex]::Match($link, '(subject=)(.)*')).Value -replace "subject=", "") -replace "Amp;", ""
		$MainFolder = $($(Get-Capalized $Subject) -replace "\.", " ") -replace "  ", " "

		if ($Subject -like "*:*") {
			$MainFolder = $($(Get-Capalized $(([regex]::Match($Subject, '(.)*:')).Value -replace ":", "").Trim()) -replace "\.", " ") -replace "  ", " "
			$SubFolder  = $($(Get-Capalized $(([regex]::Match($Subject, ':(.)*')).Value -replace ":", "").Trim()) -replace "\.", " ") -replace "  ", " "
		}

		$Group = (Get-AlternateName $Group).Trim()
		$MainFolder = (Get-AlternateName $MainFolder).Trim()

		Set-Location $Vedanta
		New-Item -Type Directory -Force $Group  | Out-Null
		Set-Location $Group

		New-Item -Type Directory -Force $MainFolder | Out-Null
		Set-Location $MainFolder
		Write-Host -NoNewline "Downloading $Group : $MainFolder"

		if ($Subject -like "*:*") {
			New-Item -Type Directory -Force $SubFolder | Out-Null
			Set-Location $SubFolder
			Write-Host -NoNewline " : $SubFolder"
		}
		Write-Host ""

		$request = Invoke-WebRequest -UseBasicParsing -Uri "$("http://www.srichalapathirao.com" + $link)"
		$URLS = ($request.Links).href | Select-String "mp3" | Get-Unique
		foreach ($URL in $URLS) {
			$FileName = Get-FixedFileName $URL.Line $MainFolder $SubFolder

			$OldFileName = Get-OldFixedFileName $URL.Line $MainFolder $SubFolder
			if ($(Test-Path $OldFileName)) {
				Move-Item -Force $OldFileName $FileName
			}

			if (!$(Test-Path $FileName)) {
				# Write-Host "$OldFileName $FileName"
				Get-RemoteFile $URL.Line $FileName
			}
		}
	}
	Set-Location $Vedanta
}

function Get-Vedanta {
	$Vedanta = ([IO.Path]::Combine($HOME, "Music", "Vedanta"))
	New-Item -Type Directory -Force $Vedanta | Out-Null
	Set-Location $Vedanta

	Get-Bharatam
	Get-Bhagavatam
	Get-BhagavadGeeta
}

function CreateDirectory($dir) {
	New-Item -ItemType Directory -Force -Path $dir | Out-Null
}

function AutoCropVideos($Encoding) {
	$PYCrop = $([IO.Path]::Combine($ToolsLocation, "Env", "python", "Projects", "PyCrop.py"))
	$Files = Get-FileNames -Recursive "mp4"

	$VideoCodec     = "hevc"
	$OUT            = "HEVC"
	$PixelFormat    = "yuv420p"
	$StartTime      = "00:00:00"
	$EndTime        = ""
	$AspectRatio    = "16:9"
	$CRF            = 23

	if ($Encoding -Like "h264") {
		$VideoCodec = $Encoding
		$OUT        = "H.264"
		$CRF        = 18
	}

	CreateDirectory $OUT
	$TMPFile = $(Join-Path $OUT "tmp.mp4")
	foreach($File in $Files) {
		CreateDirectory $(Join-Path $OUT $($File -replace $(Split-Path $File -Leaf), ""))

		if (($File -notlike "*HEVC*") -and ($File -notlike "*H.264*")) {
			if (!$(Test-Path $(Join-Path "out" $File))) {
				$Crop = python $PYCrop $File
				$VideoFilter    = "$Crop"

				# $Fno = [Int]($(Split-Path $File -Leaf)).split(' ')[0]

				$TMPFile = $(Join-Path $OUT "$File")
				Write-Host "$File : $Crop"
				if ($Encoding -Like "copy") {
					if ($EndTime -Like "*:*:*") {
						ffmpeg -y -v error -stats -i $File -ss $StartTime -to $EndTime -c copy tmp.mp4
					}
					else {
						ffmpeg -y -v error -stats -i $File -ss $StartTime -c copy tmp.mp4
					}
				}
				else {
					if ($EndTime -Like "*:*:*") {
						ffmpeg -y -v error -stats -i $File -ss $StartTime -to $EndTime -crf $CRF -filter:v "$VideoFilter" -aspect $AspectRatio -strict -2 -c:v "$VideoCodec" -pix_fmt "$PixelFormat" -c:a copy $TMPFile
					}
					else {
						ffmpeg -y -v error -stats -i $File -ss $StartTime -crf $CRF -filter:v "$VideoFilter" -aspect $AspectRatio -strict -2 -c:v "$VideoCodec" -pix_fmt "$PixelFormat" -c:a copy $TMPFile
					}
				}

				# Move-Item -Force $TMPFile $(Join-Path $OUT "$File")
			}
		}
	}
}

function TrimVideos {
	if (Test-Path "trim.txt") {
		$TrimVideos = Get-Content -Encoding UTF8 .\trim.txt
		foreach ($TrimData in $TrimVideos) {
			$DataLine  = $TrimData.Split('|')
			$VideoFile = ($DataLine[0]).Trim()
			$VTimes    = ($DataLine[1]).Split(',')
			$OUT       = (Join-Path "out" $($VideoFile -replace ".mp4", ""))
			$Count     = 0
			$Digits    = 5

			$TCount    = $VTimes.Split('-').Length
			while($TCount -ne 0) {
				$TCount = [Math]::Abs($TCount / 10)
				$Digits++

				if ($TCount -ge 10) { continue } else { break }
			}

			CreateDirectory $OUT
			foreach($VTime in $VTimes) {
				$TrimTime  = $VTime.Split('-')
				$StartTime = "00:00:00"
				$EndTime   = ($TrimTime[0] + "").Trim()

				foreach($NewEndTime in $TrimTime[1..$TrimTime.Length]) {
					$StartTime = $EndTime
					$EndTime   = ($NewEndTime + "").Trim()

					switch -Wildcard ($StartTime) {
						'[0-9][0-9]:[0-9][0-9]:[0-9][0-9]' { }
						'[0-9][0-9]:[0-9][0-9]:[0-9]'      { $StartTime = "0" + $StartTime }
						'[0-9][0-9]:[0-9][0-9]'            { $StartTime = "00:" + $StartTime }
						'[0-9]:[0-9][0-9]'                 { $StartTime = "00:0" + $StartTime }
						'[0-9][0-9]'                       { $StartTime = "00:00:" + $StartTime }
						'[0-9]'                            { $StartTime = "00:00:0" + $StartTime }
						default                            { $StartTime = "00:00:00"}
					}

					switch -Wildcard ($EndTime) {
						'[0-9][0-9]:[0-9][0-9]:[0-9][0-9]' { }
						'[0-9][0-9]:[0-9][0-9]:[0-9]'      { $EndTime = "0" + $EndTime }
						'[0-9][0-9]:[0-9][0-9]'            { $EndTime = "00:" + $EndTime }
						'[0-9]:[0-9][0-9]'                 { $EndTime = "00:0" + $EndTime }
						'[0-9][0-9]'                       { $EndTime = "00:00:" + $EndTime }
						'[0-9]'                            { $EndTime = "00:00:0" + $EndTime }
						default                            { }
					}

					$OUTFile   = Join-Path $OUT $($([String]++$Count + ".mp4") | % PadLeft $Digits '0')

					if ($EndTime -Like '[0-9][0-9]:[0-9][0-9]:[0-9][0-9]') {
						# Write-Host "ffmpeg -y -v error -stats -i $VideoFile -ss $StartTime -to $EndTime -c copy $OUTFile"
						ffmpeg -y -v error -stats -i $VideoFile -ss $StartTime -to $EndTime -c copy $OUTFile
					}
					else {
						# Write-Host "ffmpeg -y -v error -stats -i $VideoFile -ss $StartTime -to $EndTime -c copy $OUTFile"
						ffmpeg -y -v error -stats -i $VideoFile -ss $StartTime -c copy $OUTFile
					}
				}
			}
		}
	}
}

	# foreach ($Video in $Videos) {
	# 	$FileName = $Video.FullName
	# 	CreateDirectory $(Join-Path "out" $((Get-ChildItem $FileName).Directory).Name))

	# 	if (!$(Test-Path $(Join-Path "out" "$Video"))) {
	# 		$Crop = python $PYCrop $Video
	# 		Write-Host "$Video.Name : $Crop"

	# 		$VideoFilter = "$Crop"
	# 		# $VideoFilter = "$Crop, scale=512:288"
	# 		# $VideoFilter = "$Crop, scale=640:360"

	# 		$VideoCodec = "hevc"

	# 		# $PixelFormat  = "yuv420p10le"
	# 		$PixelFormat  = "yuv420p"

	# 		$Fno = [Int]($Video).split(' ')[0]
	# 		if ($Fno -le 107) {
	# 			$StartTime = "00:01:08"
	# 			$EndTime = ""
	# 		}
	# 		else {
	# 			$StartTime = "00:00:05"
	# 			$EndTime = ""
	# 		}

	# 		ffmpeg -y -v error -stats -i $Video.Name -ss $StartTime -crf 23 -filter:v "$VideoFilter" -aspect 16:9 -strict -2 -c:v "$VideoCodec" -pix_fmt "$PixelFormat" -preset:v veryslow -c:a copy $(Join-Path "out" "$Video.Name")

	# 		# ffmpeg -y -v error -stats -i $Video -filter:v "$VideoFilter" -c:v "$VideoCodec" -c:a copy $(Join-Path "out" "$Video")
	# 		# ffmpeg -y -v error -stats -i $Video -ss $StartTime -filter:v "$VideoFilter" -aspect 16:9 -strict -2 -c:v "$VideoCodec" -pix_fmt "$PixelFormat" -preset:v veryslow -c:a copy $(Join-Path "out" "$Video")
	# 		# ffmpeg -y -v error -stats -i $Video -ss $StartTime -b:v 400k -filter:v "$VideoFilter" -aspect 16:9 -strict -2 -c:v "$VideoCodec" -pix_fmt "$PixelFormat" -c:a copy $(Join-Path "out" "$Video")
	# 		# ffmpeg -y -v error -stats -i $Video -filter:v "$VideoFilter" -c:v "$VideoCodec" -pix_fmt "$PixelFormat" -crf 0 -c:a copy $($(Join-Path "out" "$Video") -replace "DAT", "mp4")

	# 		# ffmpeg -y -v error -stats -i $Video -pix_fmt "$PixelFormat" -crf 22 -filter:v "$VideoFilter" -c:v "$VideoCodec" -x265-params pass=1 -an -f mp4 NUL
	# 		# ffmpeg -y -v error -stats -i $Video -pix_fmt "$PixelFormat" -crf 22 -filter:v "$VideoFilter" -c:v "$VideoCodec" -x265-params pass=2 -c:a copy $(Join-Path "out" "$Video")

	# 		# ffmpeg -y -v error -stats -i $Video -filter:v "$Crop, scale=512:288" -c:a copy $(Join-Path "out" "$Video")

	# 		# ffmpeg -i input \
	# 		# 	-c:v libx265 -pix_fmt yuv420p \
	# 		# 	-x265-params crf=28:keyint=240:min-keyint=20 \
	# 		# 	-preset:v slow \
	# 		# 	-c:a libfdk_aac -vbr 4 \
	# 		# 	output.mp4

	# 		# ffmpeg -i '.\Part 1.DAT' -c:v libx265 -pix_fmt yuv420p -x265-params crf=28:keyint=240:min-keyint=20 -preset:v slow -c:a copy -vbr 4 '.\out\Part 1.mp4'
	# 	}
	# }

# old = crop=472:256:84:64
# new = crop=472:272:84:44

function FilterFolders {
	$CURDIR = Get-Location
	$Folders = (Get-ChildItem -Directory).FullName

	foreach ($Folder in $Folders)
	{
		Set-Location $Folder

		# Write-Host $Folder
		# ReplaceFileNames "(" " ("
		ReplaceFileNames "  " " "

		Set-Location $CURDIR
	}

	# $Folders = (Get-ChildItem -Directory).FullName

	# foreach ($Folder in $Folders) {
	# 	# Write-Host $Folder

	# 	if (Test-Path $(Join-Path $Folder "*.flac")) {
	# 		$Album = $Folder
	# 	}
	# 	else {
	# 		$Album = Join-Path $Folder "*"
	# 	}

	# 	Write-Host "$Album" "..\NewFlac"
	# 	Move-Item "$Album" "..\NewFlac"
	# }
}

function FixMoolam {
	$CURDIR = Get-Location
	$Folders = (Get-ChildItem -Directory).FullName

	foreach ($Folder in $Folders)
	{
		Set-Location $Folder

		# Write-Host $Folder
		# ReplaceFileNames "(" " ("
		# ReplaceFileNames "BH-samhita-" ""
		# ReplaceFileNames "-" " "
		# ReplaceFileNames "Adhuayam" "Adhyayam"

		# ReplaceFileNames "01 Adhyayam " ""
		# ReplaceFileNames "02 Adhyayam " ""
		# ReplaceFileNames "03 Adhyayam " ""
		# ReplaceFileNames "04 Adhyayam " ""
		# ReplaceFileNames "05 Adhyayam " ""
		# ReplaceFileNames "06 Adhyayam " ""
		# ReplaceFileNames "07 Adhyayam " ""
		# ReplaceFileNames "08 Adhyayam " ""
		# ReplaceFileNames "09 Adhyayam " ""
		# ReplaceFileNames "10 Adhyayam " ""
		# ReplaceFileNames "11 Adhyayam " ""
		# ReplaceFileNames "12 Adhyayam " ""

		# ReplaceFileNames ".mp3" " Adhyayam.mp3"

		# ReplaceFileNames "Skandamu01" "titles.txt"
		# ReplaceFileNames "Skandamu02" "titles.txt"
		# ReplaceFileNames "Skandamu03" "titles.txt"
		# ReplaceFileNames "Skandamu04" "titles.txt"
		# ReplaceFileNames "Skandamu05" "titles.txt"
		# ReplaceFileNames "Skandamu06" "titles.txt"
		# ReplaceFileNames "Skandamu07" "titles.txt"
		# ReplaceFileNames "Skandamu08" "titles.txt"
		# ReplaceFileNames "Skandamu09" "titles.txt"
		# ReplaceFileNames "Skandamu10" "titles.txt"
		# ReplaceFileNames "Skandamu11" "titles.txt"
		# ReplaceFileNames "Skandamu12" "titles.txt"

		# ReplaceFileNames "titles.txt.txt" "titles.txt"

		# cp ../cover.jpg .

		# $MP3Files = (Get-ChildItem -File -Filter "*mp3*").Name
		# $Titles = Get-Content titles.txt

		# foreach ($MP3File in $MP3Files) {
		# 	$Chapter = $MP3File.split(' ')[0]
		# 	$NewFile = $Chapter + " " + $Titles[$($([Int]$Chapter) - 1)] + ".mp3"
		# 	$NewFile = $NewFile -replace ":", " -"
		# 	# $Chapter
		# 	ReplaceFileNames $MP3File $NewFile

		# }

		# Update-ID3Files "Mrs. Manda Kulkarni"
		rm titles.txt

		Set-Location $CURDIR
	}
}