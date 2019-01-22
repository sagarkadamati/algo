function UpdateLink {

	$obj = New-Object -ComObject WScript.Shell
	$link = $obj.CreateShortcut([io.path]::combine($env:APPDATA, "Microsoft", "Windows", "Start Menu", "Programs", "Windows PowerShell", "Windows PowerShell.lnk"))
	$link.Hotkey = "Alt+Ctrl+T"
	$link.Save()

	$obj = New-Object -ComObject WScript.Shell
	$link = $obj.CreateShortcut([io.path]::combine($env:APPDATA, "Microsoft", "Windows", "Start Menu", "Programs", "VSCode.lnk"))
	$link.TargetPath = [io.path]::combine("$Tools", "VSCode", "Code.exe")
	$link.Arguments = "-r"
	$link.Hotkey = "Alt+Ctrl+E"
	$link.Save()

	# $info = @{}
	# $info.Hotkey = $link.Hotkey
	# $info.TargetPath = $link.TargetPath
	# $info.LinkPath = $link.FullName
	# $info.Arguments = $link.Arguments
	# $info.Target = try {Split-Path $info.TargetPath -Leaf } catch { 'n/a'}
	# $info.Link = try { Split-Path $info.LinkPath -Leaf } catch { 'n/a'}
	# $info.WindowStyle = $link.WindowStyle
	# $info.IconLocation = $link.IconLocation

	# New-Object PSObject -Property $info
	# $MYPROFILE = ". \'" + $Projects + $DirectorySperator + "algos" + $DirectorySperator + "ps1" + $DirectorySperator + "Microsoft.PowerShell_profile.ps1'"
	# Write-Output $MYPROFILE > $profile
}

function Get-Shortcut {
	param(
		$path = $null
	)

	$obj = New-Object -ComObject WScript.Shell

	if ($path -eq $null) {
		$pathUser = [System.Environment]::GetFolderPath('StartMenu')
		$pathCommon = $obj.SpecialFolders.Item('AllUsersStartMenu')
		$path = dir $pathUser, $pathCommon -Filter *.lnk -Recurse
	}
	if ($path -is [string]) {
		$path = dir $path -Filter *.lnk
	}
	$path | ForEach-Object {
		if ($_ -is [string]) {
			$_ = dir $_ -Filter *.lnk
		}
		if ($_) {
			$link = $obj.CreateShortcut($_.FullName)

			$info = @{}
			$info.Hotkey = $link.Hotkey
			$info.TargetPath = $link.TargetPath
			$info.LinkPath = $link.FullName
			$info.Arguments = $link.Arguments
			$info.Target = try {Split-Path $info.TargetPath -Leaf } catch { 'n/a'}
			$info.Link = try { Split-Path $info.LinkPath -Leaf } catch { 'n/a'}
			$info.WindowStyle = $link.WindowStyle
			$info.IconLocation = $link.IconLocation

			New-Object PSObject -Property $info
		}
	}
}
