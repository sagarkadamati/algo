. "$PSScriptRoot\Audio.ps1"
. "$PSScriptRoot\Video.ps1"

function GetBhagavataSkandam($dir, $sk, $end) {
	$cdir = Get-Location
	if (!$(Test-Path $dir)) {
		New-Item -Type Directory $dir
	}
	Set-Location $dir
	if (!$(Test-Path "html")) {
		New-Item -Type Directory "html"
	}

	$count = 1
	foreach($i in 1..$end ) {
		try {
			$html = New-Object -ComObject "HTMLFile"
			# echo "http://telugubhagavatam.org/?tebha&Skanda=${sk}&Ghatta=${i}"
			if (Test-Path "html/${count}.html") {
				$html.IHTMLDocument2_write($(Get-Content "html/${count}.html" -raw))
			} else {
				Invoke-WebRequest -Uri "http://telugubhagavatam.org/?tebha&Skanda=${sk}&Ghatta=${i}" -OutFile "${i}.html"
				$html.IHTMLDocument2_write($(Get-Content "${i}.html" -raw))
			}
			$title = ($html.all.tags("span") | foreach { if ($_.classname -match "ghatta") { $_.outerText} })
			if ($title -notlike "") {
				$cstr = ($count.ToString()).PadLeft($end.ToString().Length, '0')
				$html.all.tags("p") | foreach { if ($_.classname -match "meaning") { $_.outerText; echo ""} } | Out-File -Encoding utf8 "${cstr} ${title}.md"
				if (!(Test-Path "html/${count}.html")) {
					Move-Item "${i}.html" "html/${count}.html"
				}
				$count = $count + 1
			} else {
				Remove-Item "${i}.html"
			}
		} catch {
			write-warning 'Skandam $sk Ghatta $1 skt found'
			break
		}
	}

	Set-Location $cdir
}

function GetBhagavatam {
	GetBhagavataSkandam "01 ప్రథమ స్కంధము" 1 41
	GetBhagavataSkandam "02 ద్వితీయ స్కంధము" 2 36
	GetBhagavataSkandam "03 తృతీయ స్కంధము" 3 57
	GetBhagavataSkandam "04 చతుర్థ స్కంధము" 4 28
	GetBhagavataSkandam "05 పంచమ స్కంధము - పూర్వ" 5.1 16
	GetBhagavataSkandam "06 పంచమ స్కంధము - ఉత్తర" 5.2 8
	GetBhagavataSkandam "07 షష్ఠ స్కంధము" 6 17
	GetBhagavataSkandam "08 సప్తమ స్కంధము" 7 17
	GetBhagavataSkandam "09 అష్టమ స్కంధము" 8 93
	GetBhagavataSkandam "10 నవమ స్కంధము" 9 54
	GetBhagavataSkandam "11 దశమ స్కంధము - పూర్వ" 10.1 211
	GetBhagavataSkandam "12 దశమ స్కంధము - ఉత్తర" 10.2 91
	GetBhagavataSkandam "13 ఏకాదశ స్కంధము" 11 19
	GetBhagavataSkandam "14 ద్వాదశ స్కంధము" 12 13
}

Export-ModuleMember -Function ConcatVideos, AutoCropVideos, AnalizeVideos, GenVideos
Export-ModuleMember -Function Get-SriChalapathiRaoAudio, Update-ID3Files, GetBhagavatam