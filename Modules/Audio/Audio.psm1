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

function Get-Parvam($URL) {
	$response = Invoke-WebRequest -Uri $URL
	$Links = ($response.Links).href | Select-String -Pattern "mp3$"

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
			Invoke-WebRequest -Uri $link.Line -OutFile $(Join-Path $Parvam $NewFileName)
		}
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

function Get-Vedanta {
	New-Item -Type Directory "Vedanta"
	Set-Location "Vedanta"

	Get-Bharatam
}