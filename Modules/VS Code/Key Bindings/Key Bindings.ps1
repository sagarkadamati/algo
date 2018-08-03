function Get-VSKeys {
	# $jsondata  = Get-json $(Join-Path $PSScriptRoot "DeRegister.json")
	# $jsondata += Get-json $(Join-Path $PSScriptRoot "Cancel.json")
	# $jsondata += Get-json $(Join-Path $PSScriptRoot "Cursor.json")
	# $jsondata += Get-json $(Join-Path $PSScriptRoot "DeRegister.json")
	# $jsondata += Get-json $(Join-Path $PSScriptRoot "Editor.json")
	# $jsondata += Get-json $(Join-Path $PSScriptRoot "Explorer.json")
	# $jsondata += Get-json $(Join-Path $PSScriptRoot "Git.json")
	# $jsondata += Get-json $(Join-Path $PSScriptRoot "List.json")
	# $jsondata += Get-json $(Join-Path $PSScriptRoot "Search.json")
	# $jsondata += Get-json $(Join-Path $PSScriptRoot "Settings.json")
	# $jsondata += Get-json $(Join-Path $PSScriptRoot "Tasks.json")
	# $jsondata += Get-json $(Join-Path $PSScriptRoot "UI.json")

	$jsondata  = Get-Content $(Join-Path $PSScriptRoot "De Register.json")
	$jsondata += Get-Content $(Join-Path $PSScriptRoot "Focus.json")
	$jsondata += Get-Content $(Join-Path $PSScriptRoot "Cancel.json")
	$jsondata += Get-Content $(Join-Path $PSScriptRoot "Cursor.json")
	$jsondata += Get-Content $(Join-Path $PSScriptRoot "Editor.json")
	$jsondata += Get-Content $(Join-Path $PSScriptRoot "Source Browser.json")
	$jsondata += Get-Content $(Join-Path $PSScriptRoot "UI.json")

	$jsondata += Get-Content $(Join-Path $PSScriptRoot "Config"   | Join-Path -ChildPath "Key Bindings.json")
	$jsondata += Get-Content $(Join-Path $PSScriptRoot "Config"   | Join-Path -ChildPath "Settings.json")
	$jsondata += Get-Content $(Join-Path $PSScriptRoot "Config"   | Join-Path -ChildPath "Tasks.json")

	$jsondata += Get-Content $(Join-Path $PSScriptRoot "Panel"    | Join-Path -ChildPath "Debug.json")
	$jsondata += Get-Content $(Join-Path $PSScriptRoot "Panel"    | Join-Path -ChildPath "Output.json")
	$jsondata += Get-Content $(Join-Path $PSScriptRoot "Panel"    | Join-Path -ChildPath "Problems.json")
	$jsondata += Get-Content $(Join-Path $PSScriptRoot "Panel"    | Join-Path -ChildPath "Terminal.json")

	$jsondata += Get-Content $(Join-Path $PSScriptRoot "Side Bar" | Join-Path -ChildPath "Debug.json")
	$jsondata += Get-Content $(Join-Path $PSScriptRoot "Side Bar" | Join-Path -ChildPath "Explorer.json")
	$jsondata += Get-Content $(Join-Path $PSScriptRoot "Side Bar" | Join-Path -ChildPath "Extensions.json")
	$jsondata += Get-Content $(Join-Path $PSScriptRoot "Side Bar" | Join-Path -ChildPath "Find And Replace.json")
	$jsondata += Get-Content $(Join-Path $PSScriptRoot "Side Bar" | Join-Path -ChildPath "Git.json")

	$jsondata += Get-Content $(Join-Path $PSScriptRoot "Widgets"  | Join-Path -ChildPath "Quick Open.json")
	$jsondata += Get-Content $(Join-Path $PSScriptRoot "Widgets"  | Join-Path -ChildPath "Find And Replace.json")
	$jsondata += Get-Content $(Join-Path $PSScriptRoot "Widgets"  | Join-Path -ChildPath "Suggest Widget.json")

	Write-Output "["
	$jsondata
	Write-Output "]"
}
