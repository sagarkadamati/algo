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

function Update-ID3($AudioFile, $AlbumArtist) {
	if ($AudioFile) {
		$File   = (Get-ChildItem $AudioFile)
		$Title  = $File.BaseName
		$Album  = ((Get-Location).Path -split [regex]::Escape([IO.Path]::DirectorySeparatorChar))[-1]
		$Genre  = ($File.Directory).Name
		$Track  = ($Title -split " ")[0]
		$Artist = ""

		if ($AlbumArtist) {
			$Artist = $AlbumArtist
		}

		if ($Album -notmatch $Genre) {
			$Genre = $Album + " (" + $Genre + ")"
		}

		$MID3V2 = (Join-Path (where.exe python | gci).DirectoryName "Scripts") | Join-Path -ChildPath "mid3v2"
		python $MID3V2 --artist="$Artist" --album="$Album" --song="$Title" --genre="$Genre" --track="$Track" "$AudioFile"
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