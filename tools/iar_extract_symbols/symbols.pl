#!/usr/bin/perl

# Parameters:
# $ARGV[0]: $TOOLKIT_DIR$
# $ARGV[1]: $FILE_PATH$
# $ARGV[2]: $PROJ_DIR$

$symbols_txt = $ARGV[1];
$symbols_txt =~ s/^[\w\W]{1,1}\:.*\\(.*)\.a/\1/;
$symbols_txt = $ARGV[2] . "\\" . $symbols_txt . "_symbols.txt";

$cmd_string = "\"" . $ARGV[0] . "\\bin\\iarchive.exe\" --symbols \"" . $ARGV[1] . "\" \> \"" . $symbols_txt . "\"";
system($cmd_string);

open(SYMBOLS, $symbols_txt);
@symbols = <SYMBOLS>;
close(SYMBOLS);
foreach $symbol (@symbols)
{
  ($obj,$symbol) = split(/[ ]{1,}/,$symbol);
  $symbol = "--keep " . $symbol;
}
open(SYMBOLS, ">" . $symbols_txt);
print SYMBOLS @symbols;
close(SYMBOLS);

$prj_symbols_txt = $ARGV[2] . "\\symbols.txt";
open(SYMBOLS, $prj_symbols_txt);
@symbols = <SYMBOLS>;
close(SYMBOLS);
open(SYMBOLS, ">" . $prj_symbols_txt);
print SYMBOLS "-f " . $symbols_txt . "\n\n";
print SYMBOLS @symbols;
close(SYMBOLS);

$cmd_string = "copy \"" . $ARGV[2] . "\\dummy.o\" \"" . $ARGV[1] . "_dummy.o\"";
system($cmd_string);
