#!/usr/bin/perl -w
use strict;
use Getopt::Std;
use English '-no_match_vars';

#####################Options####################################################
#the options and there flags used on the command line
my $max_vh_num=60;
my $passwd_length=8;
my @reserved_vh=();
my %reserved_vh;
my %used_vh;
my $tomcat_conf_dir="/usr/local/tomcat/conf";
my $passwd_encrypt_prog="/usr/local/bin/md5passwd";
for(@reserved_vh){
    $reserved_vh{$_}=1;
}

my %options=(
             'b' => "/usr/local/tomcat/conf",             #base - the b
             'u' => "/user.list",                        
             't' => "/created.user.list",
	     'w' => "/usr/local/tomcat/users",             #rw directory
             'o' => "",                                    #output
	     'p' => "",                                    #print the user details
             );
my $vhstartpattern="stud";
getopts('b:u:t:o:p:',\%options);
my $userlist=$options{b}.$options{u};
my $existinguserlist=$options{b}.$options{t};
my $fingerprog="finger -m ";
my %userdetails;
my @userlist;
my @existinguserlist;
my (%existingusers,%existing_vh_numbers);
my $USERLIST;
#####################Global variables###########################################

open ($USERLIST,$existinguserlist) or die "couldn't open user list file $userlist!";
@existinguserlist=<$USERLIST>;
close $USERLIST;

open ($USERLIST,$userlist) or die "couldn't open new user list file $userlist!";
@userlist=<$USERLIST>;
close $USERLIST;

for(@existinguserlist){
    if(/^\s*\#/ or /^\s*$/){
	next;
    }
    my %user;
    ($user{login},
     $user{passwd},
     $user{homedir},
     $user{rwdir},
     $user{vh})=split(' ',$_);
    $used_vh{$user{vh}}=1;
    $existingusers{$user{login}}={%user};
    $user{vh} =~ /$vhstartpattern(\w+)/;
    $existing_vh_numbers{$1}=1;
}

#print the user details
if($options{p}){
    if(exists ($existingusers{$options{p}})){
	%userdetails=%{ $existingusers{$options{p}} };
	$FORMAT_NAME = "USER_HEADER"; write;	
	$FORMAT_NAME = "USER"; write;	
    }else{
	print "The user $options{p} does not exists!\n";
    }
    exit(0);
}

    my @free_vh;
for(1..$max_vh_num){
    if((!exists($used_vh{$_})) && (!exists($reserved_vh{$_}))){
	push @free_vh,$_;
    }
}
#go throught the list of users we to have
for(@userlist){
    if(/^\s*\#/ or /^\s*$/){
	next;
    }
    s/\s//g;
    if(! exists($existingusers{$_})){
	$userdetails{login}=$_;
	($userdetails{passwd},
         $userdetails{encr_passwd})=passwd_generate($passwd_length);
	$userdetails{homedir}=home_dir($_);
	$userdetails{homedir}=rw_dir($_);	
 	$userdetails{vh}=shift @free_vh;
	$FORMAT_NAME = "USER"; write;
        my $vhsetting=<<VH;
    <!-- A virtual host for user $userdetails{login}->{login} -->

    <Host name="${vhstartpattern}$userdetails{vh}.ise.jct.ac.il" debug="0" appBase="noapplic"
     unpackWARs="true" autoDeploy="true">

     <Context path="/manager" docBase="/usr/local/tomcat/server/webapps/manager" debug="0" privileged="true">
      <Realm className="org.apache.catalina.realm.MemoryRealm" digest="md5"
      pathname="${tomcat_conf_dir}/${vhstartpattern}$userdetails{vh}/tomcat-users.xml"/>
     </Context>

     <Context path="/calendar" docBase="$userdetails{homedir}/javaserver" debug="0" privileged="true">
     </Context>
         <Logger className="org.apache.catalina.logger.FileLogger"
                  directory="$userdetails{homedir}/javaserver"  prefix="localhost_log." suffix=".txt"
                timestamp="true"/>

         <!--Define properties for each web application.  This is only needed
           if you want to set non-default properties, or have web application
           document roots in places other than the virtual hosts appBase
           directory.  -->

      <!-- Tomcat Root Context -->
         <!--
        <Context path="" docBase="ROOT" debug="0"/> -->

      <!-- Default Context, for auto-created Contexts -->
         <DefaultContext reloadable="true" crossContext="true"/>

         <Environment name="maxExemptions" type="java.lang.Integer"
                       value="15"/>
         <Parameter name="context.param.name" value="context.param.value"
                      override="false"/>
       </Host>

VH

create_user_perms("${tomcat_conf_dir}/${vhstartpattern}$userdetails{vh}/tomcat-users.xml");
    }
}

sub create_user_perms{
    my $filename=shift;
    my ($username,$passwd)=@_;
    my $F;
    my $tuf=<<TU;
<?xml version='1.0' encoding='utf-8'?>
<tomcat-users>
  <user username="$username" password="$passwd" roles="standard,manager"/>
</tomcat-users>

TU
    open ($F,$filename) or warn "couldn't open the passwd file $filename!";
    print $tuf;
    close $F;

}

sub rw_dir{
    my $login=shift;
    my $dir="$options{w}/$login";
    `mkdir -m 1777 $dir`;
    return $dir;
}

sub home_dir{
    my $login=shift;
    my $finger_out=`$fingerprog $login`;
    $finger_out=~/Directory:\s*(.*?)\s+/;
    return $1;
}

# sub passwd_generate { 
#     my ($passwdlength)= @_; 
#     my $result=""; 
#     my $passwdkey="1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
#     while ($passwdlength) { 
# 	$result.=substr($passwdkey,rand(length($passwdkey)),1); 
# 	$passwdlength--; 
#     } 
#     return($result); 
#} 
sub passwd_generate{
    my $word_file="/usr/dict/words";
    my $WORDS;
    open($WORDS,"<$word_file");
    my @words=<$WORDS>;
    close $WORDS;
    srand(time ^ $$ ^ unpack "%L*", `/usr/bin/ps -ef | gzip`);
    my $digit=int(rand(9));
    my $letter=chr(int(rand(25)+65)); #get a capital letter
    my $replace=chr(int(rand(25)+97));#get a lower case letter for replacing a '
        
        my $to_pass=$words[rand($#words)]; #get a word (index is a rand value up to last index of array)
    chomp($to_pass);
    $to_pass.=$words[rand($#words)]; #add on a 2nd  word
    my $placing=rand(6);  #
    my $to_pass_a=substr($to_pass,0,$placing).$digit.substr($to_pass,$placing,7-$placing);
    $placing=rand(7);
    my $pass=substr($to_pass_a,0,$placing).$letter.substr($to_pass_a,$placing,8-$placing);
    my $encr_out=`$passwd_encrypt_prog $pass`;
    $encr_out=~/^(.*?):(.*)$/;
    chomp $encr_out;
    return ($pass,$encr_out);
}


format USER_HEADER =
LOGIN               PASSWD                      HOMEDIR                                    RWDIR                    VH
-----------    ---------------    -----------------------------------------------    --------------------------   ------
.

format USER =
@<<<<<<<<<<    @<<<<<<<<<<<<<<    @<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    @<<<<<<<<<<<<<<<<<<<<<<<<<   @<<<<<
$userdetails{login}, $userdetails{passwd},$userdetails{homedir}, $userdetails{rwdir} ,$userdetails{vh}
.
