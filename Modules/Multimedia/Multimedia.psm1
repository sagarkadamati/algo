. "$PSScriptRoot\Audio.ps1"
. "$PSScriptRoot\Video.ps1"

function GetBhagavataSkandam($dirno, $dir, $sk, $end) {
	$cdir = Get-Location
	if (!$(Test-Path "$dirno $dir")) {
		New-Item -Type Directory "$dirno $dir"
	}
	Set-Location "$dirno $dir"
	
	echo "$dirno"
	echo "# <div style='text-align: center; color:#262626;font-size:16.0pt;font-weight:normal'>$dir</div>" >> ../భాగవతం.md
	echo "" >> ../భాగవతం.md

	if (!$(Test-Path "html")) {
		New-Item -Type Directory "html"
	}

	$count = 1
	foreach($i in 1..$end ) {
		try {
			$html = New-Object -ComObject "HTMLFile"
			# echo "http://telugubhagavatam.org/?tebha&Skanda=${sk}&Ghatta=${i}"
			if (Test-Path "html/${i}.html") {
				$html.IHTMLDocument2_write($(Get-Content "html/${i}.html" -raw))
			} else {
				Invoke-WebRequest -Uri "http://telugubhagavatam.org/?tebha&Skanda=${sk}&Ghatta=${i}" -OutFile "${i}.html"
				$html.IHTMLDocument2_write($(Get-Content "${i}.html" -raw))
			}
			$title = ($html.all.tags("span") | foreach { if ($_.classname -match "ghatta") { $_.outerText} })
			if ($title -notlike "") {
				$cstr = ($count.ToString()).PadLeft($end.ToString().Length, '0')
				$html.all.tags("p") | foreach {
					if ($_.classname -match "meaning") {
						echo "<div style='text-align: justify; color:#262626;font-size:12.0pt;font-weight:normal'>"
						try {
							$_.outerText.replace("`n","`n`n").replace("`n`n`n","`n`n").replace("`n(1)","1.").replace("`n(2)","2.").replace("`n(3)","3.").replace("`n(4)","4.").replace("`n(5)","5.").replace("`n(6)","6.").replace("`n(7)","7.").replace("`n(8)","8.").replace("`n(9)","9.").replace("`n(10)","10.").replace("`n(11)","11.").replace("`n(12)","12.").replace("`n(13)","13.").replace("`n(14)","14.").replace("`n(15)","15.").replace("`n(16)","16.").replace("`n(17)","17.").replace("`n(18)","18.").replace("`n(19)","19.").replace("`n(20)","20.").replace("`n(21)","21.").replace("`n(22)","22.").replace("`n(23)","23.").replace("`n(24)","24.").replace("`n(25)","25.").replace("`n(26)","26.").replace("`n(27)","27.").replace("`n(28)","28.").replace("`n(29)","29.").replace("`n(30)","30.").replace("`n(31)","31.").replace("`n(32)","32.").replace("`n(33)","33.").replace("`n(34)","34.").replace("`n(35)","35.").replace("`n(36)","36.").replace("`n(37)","37.").replace("`n(38)","38.").replace("`n(39)","39.").replace("`n(40)","40.").replace("`n1)","1.").replace("`n2)","2.").replace("`n3)","3.").replace("`n4)","4.").replace("`n5)","5.").replace("`n6)","6.").replace("`n7)","7.").replace("`n8)","8.").replace("`n9)","9.").replace("`n10)","10.")
						} catch {
							echo "ERROR"
							$_.outerText
						}
						echo "</div>"
						echo ""
					}
				} | Out-File -Encoding utf8 "${cstr} ${title}.md"
				echo "## <div style='text-align: center; color:#262626;font-size:12.0pt;font-weight:normal'>${title}</div>" >> ../భాగవతం.md
				# >> ../భాగవతం.md
				# echo '</div>' >> ../భాగవతం.md
				# echo '<div style="text-align: center; color:#262626">' >> ../భాగవతం.md
				# echo "${title}" >> ../భాగవతం.md
				# echo '</div>' >> ../భాగవతం.md
				# echo "" >> ../భాగవతం.md
				# echo "## <center>${title}</center>" >> ../భాగవతం.md
				echo "" >> ../భాగవతం.md
				cat "${cstr} ${title}.md" >> ../భాగవతం.md
				if (!(Test-Path "html/${count}.html")) {
					Move-Item "${i}.html" "html/${count}.html"
				}
				$count = $count + 1
			} else {
				Remove-Item "${i}.html"
			}
		} catch {
			write-warning "Skandam $sk Ghatta $1 skt found, $i"
			break
		}
	}

	Set-Location $cdir
}

function GetBhagavatam {
	Remove-Item "భాగవతం.md" -ErrorAction Ignore
	GetBhagavataSkandam "01" "ప్రథమ స్కంధము" 1 41
	GetBhagavataSkandam "02" "ద్వితీయ స్కంధము" 2 36
	GetBhagavataSkandam "03" "తృతీయ స్కంధము" 3 57
	GetBhagavataSkandam "04" "చతుర్థ స్కంధము" 4 28
	GetBhagavataSkandam "05" "పంచమ స్కంధము - పూర్వ" 5.1 16
	GetBhagavataSkandam "06" "పంచమ స్కంధము - ఉత్తర" 5.2 8
	GetBhagavataSkandam "07" "షష్ఠ స్కంధము" 6 17
	GetBhagavataSkandam "08" "సప్తమ స్కంధము" 7 17
	GetBhagavataSkandam "09" "అష్టమ స్కంధము" 8 93
	GetBhagavataSkandam "10" "నవమ స్కంధము" 9 54
	# GetBhagavataSkandam "11" "దశమ స్కంధము - పూర్వ" 10.1 211
	GetBhagavataSkandam "11" "దశమ స్కంధము - పూర్వ" 10.1 198
	GetBhagavataSkandam "12" "దశమ స్కంధము - ఉత్తర" 10.2 91
	GetBhagavataSkandam "13" "ఏకాదశ స్కంధము" 11 19
	GetBhagavataSkandam "14" "ద్వాదశ స్కంధము" 12 13
}

Export-ModuleMember -Function ConcatVideos, AutoCropVideos, AnalizeVideos, GenVideos
Export-ModuleMember -Function Get-SriChalapathiRaoAudio, Update-ID3Files, GetBhagavatam