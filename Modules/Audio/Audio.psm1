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
		$Genre = ($File.Directory).Name
		$Track = ($File.BaseName -split " ")[0]

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

function Get-FixedFileName($tmp, $main, $sub) {
	$FileName = Split-Path $tmp -Leaf
	$FileName = $FileName -replace "MP3", "mp3"
	$FileName = StringSplitCaps $FileName

	if ($FileName -like "*_*") {
		$FileName = $FileName -replace $($main + "_"), ""
		$FileName = $FileName -replace $($main + ""), ""
		$FileName = $FileName -replace $($sub + "_"), ""
		$FileName = $FileName -replace $($sub + ""), ""
		$FileName = $FileName -replace "_", ","
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
	
			if (!$(Test-Path $FileName)) {
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