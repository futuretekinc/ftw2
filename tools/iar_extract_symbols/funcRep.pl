#! /usr/bin/perl 


$argc = @ARGV;
$file2parse = $ARGV[0];
$patt_to_replace = $ARGV[1];
$replace_patt = $ARGV[2];
$exe_path = $ARGV[3];
$inp_file = "rom.a";
$output_path = $ARGV[3];



my @old_func_names;

if($argc < 3)
{
	print "Usage: funcRep <file2parse> <Pattern to Find> <Pattern to Replace> <iobjmanip executable Path> <ROM file>\n\n"; 
	exit;
}


if ($argc > 3)
{
    $inp_file = $ARGV[4];
}
if ($argc > 4)
{
	$output_path = $ARGV[5];
}

$out_file = $output_path."/rom-2.a"; # Do not change this name
$newfile = $output_path."/rom-final.a";
#print "<ARGV-0> $ARGV[0]\n\n<ARGV-1> $ARGV[1]\n\n<ARGV-2> $ARGV[2]\n\n<ARGV-3> $ARGV[3]\n\n<ARGV-4> $ARGV[4]";


if (-e $file2parse)
{
	open(FILE_2_PARSE, $file2parse)or die "Cant open $file2parse";

	foreach my $line (<FILE_2_PARSE>)
	{
		$line =~ s/\r//g; 
		@after_split = split(/ /,$line);
		push(@old_func_names,$after_split[1]);
	}
	close(FILE_2_PARSE);
}



my $i = 1;

my $flag = 0;
my $old_out_file = $out_file;
my @org_inp_file;
my $new_out_file;

push(@org_inp_file,$inp_file);

foreach my $name (@old_func_names)
{
	my $old_name = $name;
	if($name =~ m/$patt_to_replace/)
	{
		#print "Match $patt_to_replace Found\n";
		$name =~ s/$patt_to_replace/$replace_patt/g;
		#print $name;		
	}
	#iobjmanip --rename_symbol oldname=newname inputfile outputfile	

	if ($flag)
	{
		$inp_file = $old_out_file;
		push(@org_inp_file,$inp_file);
		#print "PUSHING FILE = <$inp_file\n";
	}

	my $cmd = "\"$exe_path\"\\iobjmanip.exe --rename_symbol $old_name=$name $inp_file $out_file";

	$cmd =~ s/\n//g; 

	#print "FILE = $inp_file\n";
	#print "CMD = $cmd\n";
	#$a = <STDIN>;
	cmd_exec($cmd);

	$old_out_file = $out_file;

	@temp_out_file = split(/-/,$out_file);

	@temp = split(/\./,$temp_out_file[1]);

	$temp[0] = $temp[0] + 1;

	$temp_join = join('.',@temp); 

	$out_file = join('-',$temp_out_file[0],$temp_join);

	$flag = 1;

}

rename $old_out_file,$newfile || die ( "Error in renaming to $newfile" );

for(my $i = 1;$i<=($#org_inp_file);$i++)
{
	if(-e $org_inp_file[$i])
	{
		unlink($org_inp_file[$i]);
	}
}
	

if (-e $newfile)
{
	print "\n\nNew Output File = $newfile Created\n\n\n\n";

}
else
{
	print "\n\nOutput File Could Not be Created\n\n\n\n";
}



sub cmd_exec
{
	my $cmd = shift;

       $cmd_send="$cmd 2>&1";
	#print "$cmd_send\n";

        open(CMD, "$cmd_send |") or die "Can't run '$cmd_send'\n$!\n";

	while(<CMD>)
	{ # each line of output is put into $_
        	#print $_; 
	}

        close(CMD);
	return;
}
