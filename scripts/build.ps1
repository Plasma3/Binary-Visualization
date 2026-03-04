$tmp_folder = "./.temp"

function DXC_Build {
	param ($target, $entry, $file, $output)

	$output = "{0}/{1}.spv" -f $tmp_folder, $output;

	Write-Output ("Compiling {0,-32} : {1,-10} to {2} with {3} into {4}" -f ($file, $entry, $target, "dxc", $output));
	
	dxc -WX -Zi -spirv -T $target -E $entry $file -Fo $output
}

function GCC_Build {
	param ($file, $output, $flags)

	$output = "{0}/{1}.o" -f $tmp_folder, $output;

	Write-Output ("Compiling {0,-20} with {1} to {2}" -f ($file, "gcc", $output));
	gcc $flags $file -c -o $output
	
	if ($LASTEXITCODE -ne 0) {
		Write-Error ("Build of {0} failed!" -f $file)
		break
	}
}

function GCC_BuildExe {
	param ($file, $output, $flags)

	# $output = "{0}/{1}.o" -f $tmp_folder, $output;

	Write-Output ("Compiling {0,-20} with {1} to {2}" -f ($file, "gcc", $output));
	gcc $flags $file -o $output
	
	if ($LASTEXITCODE -ne 0) {
		Write-Error ("Build of {0} failed!" -f $file)
		break
	}
}

function GPP_Build {
	param ($file, $output, $flags)

	Write-Error "g++ Compiler doesn't work atm!";
	break;

	Write-Output ("Compiling {0} with {1} to {2}" -f ($file, "g++", $output));
	C:\msys64\usr\bin\g++ $flags $file -c -o $output
	
	if ($LASTEXITCODE -ne 0) {
		Write-Error ("Build of {0} failed!" -f $file)
		break
	}
}

function GCC_Link {
	param ($files, $output, $flags)

	$files = foreach($item in $files) {
		"{0}/{1}.o" -f $tmp_folder, $item
	};
	
	Write-Output ("Linking into {0}" -f ($output));

	gcc $files $flags -o $output

	if ($LASTEXITCODE -ne 0) {
		Write-Error ("Linking into {0} failed!" -f $output);
		break;
	}
}

function GPP_Link {
	param ($files, $output, $flags)

	$files = foreach($item in $files) {
		"{0}/{1}.o" -f $tmp_folder, $item
	};
	
	Write-Output ("Linking into {0}" -f ($output));

	g++ $files $flags -o $output

	if ($LASTEXITCODE -ne 0) {
		Write-Error ("Linking into {0} failed!" -f $output);
		break;
	}
}