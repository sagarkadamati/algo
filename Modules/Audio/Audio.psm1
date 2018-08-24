function Get-MovieURLs($URLLink) {
	$Response = Invoke-WebRequest -Uri $URLLink

	$Urls = ($Response.Links | Where-Object {$_.href -like "*flac*download.html"}).href | Get-Unique

	return $Urls
}

function Get-PageCount($Page) {
	$Response = Invoke-WebRequest -Uri $Page
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
		$COVER = Get-ChildItem -Name -File -Filter "cover.*" -Path ($File.Directory).Name
		if ($COVER) {
			$COVER = Get-ChildItem -Name -File -Filter "cover.*" -Path .
		}

		$COVER = "cover.jpg"
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

		# $MID3V2 = (Join-Path (where.exe python | gci).DirectoryName "Scripts") | Join-Path -ChildPath "mid3v2"
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
	$response = Invoke-WebRequest -Uri $URL
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

			New-Item -Type Directory -Force $Parvam

			# Write-Output "Invoke-WebRequest -Uri $link -OutFile $(Join-Path $Parvam $NewFileName)"
			$FileName = $(Join-Path $Parvam $NewFileName)
			if (!$(Test-Path $FileName)) {
				Get-RemoteFile $link.Line $FileName
			}
		}
	}
}

function Get-Bharatam {
	New-Item -Type Directory "Maha Bharatam"
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
		Remove-Item "cover.jpg"
	}

	Set-Location ..
}

function Get-RemoteFile($URL, $FileName) {
	if (!$FileName) {
		$FileName = $(Split-Path $URL -Leaf)
	}

	Invoke-WebRequest -Uri $URL -OutFile $FileName
}

function Get-DasamaSkandam {
	New-Item -Type Directory -Force "Dasama Skandam"
	Set-Location "Dasama Skandam"

	$request = Invoke-WebRequest -Uri "http://www.srichalapathirao.com/discourses?category=bhakti_dasama"
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
	New-Item -Type Directory -Force "Bhagavatam"
	Set-Location "Bhagavatam"

	Get-DasamaSkandam

	Copy-Item $([IO.Path]::Combine($ToolsLocation, "Env", "Album Arts", "Dasama Skandam.jpg")) cover.jpg
	Update-ID3Files "Sri Chalapathi Rao"
	if (Test-Path "cover.jpg")
	{
		Remove-Item "cover.jpg"
	}

	Set-Location ..
}

function Get-Vedanta {
	New-Item -Type Directory -Force "Vedanta"
	Set-Location "Vedanta"

	Get-Bharatam
	Get-Bhagavatam
}