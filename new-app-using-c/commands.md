# 7z

## Man 7z
7z(1)                                     General Commands Manual                                     7z(1)

NAME
       7z - A file archiver with high compression ratio format

SYNOPSIS
       7z <command> [<switches>... ] <archive_name> [<file_names>... ] [<@listfiles>... ]

DESCRIPTION
       7-Zip  is  a  file archiver supporting 7z (that implements LZMA compression algorithm featuring very
       high compression ratio), LZMA2, XZ, ZIP, Zip64, CAB, RAR (if the non-free p7zip-rar package  is  in‐
       stalled),  ARJ,  GZIP, BZIP2, TAR, CPIO, RPM, ISO, most filesystem images and DEB formats.  Compres‐
       sion ratio in the new 7z format is 30-50% better than ratio in ZIP format.

       7z uses plugins to handle archives, so it might be slightly slower than 7za(1) but can  handle  more
       archive formats.

COMMANDS
       a      Add files to archive

       b      Benchmark

       d      Delete files from archive

       e      Extract files from archive (without using directory names)

       h      Calculate hash values for files

       i      Show information about supported formats

       l      List contents of archive

       rn     Rename files in archive

       t      Test integrity of archive

       u      Update files to archive

       x      eXtract files with full paths

SWITCHES
       --     Stop switches parsing

       -ai[r[-|0]]{@listfile|!wildcard}
              Include archives

       -ax[r[-|0]]{@listfile|!wildcard}
              Exclude archives

       -ao{a|s|t|u}
              Set Overwrite mode

       -an    Disable archive_name field

       -bb[0-3]
              Set output log level

       -bd    Disable progress indicator

       -bs{o|e|p}{0|1|2}
              Set output stream for output/error/progress line

       -bt    Show execution time statistics

       -i[r[-|0]]{@listfile|!wildcard}
              Include filenames

       -m{Parameters}
              Set  Compression Method (see /usr/share/doc/p7zip/DOC/MANUAL/cmdline/switches/method.htm from
              the p7zip-full package for a list of methods)

       -o{Directory}
              Set Output directory

       -p{Password}
              Set Password (NOTE: this flag does not work with 7zr)

       -r[-|0]
              Recurse subdirectories (CAUTION: this flag does not do what you think, avoid using it)

       -sa{a|e|s}
              Set archive name mode

       -scc{UTF-8|WIN|DOS}
              Set charset for for console input/output

       -scs{UTF-8|UTF-16LE|UTF-16BE|WIN|DOS|{id}}
              Set charset for list files

       -scrc[CRC32|CRC64|SHA1|SHA256|*]
              Set hash function for x, e, h commands

       -sdel  Delete files after compression

       -seml[.]
              Send archive by email

       -sfx[{name}]
              Create SFX archive

       -si[{name}]
              Read data from stdin (e.g. tar cf - directory | 7z a -si directory.tar.7z)

       -slp   Set Large Pages mode

       -slt   Show technical information for l (List) command

       -snh   Store hard links as links

       -snl   Store symbolic links as links

       -sni   Store NT security information

       -sns[-]
              Store NTFS alternate streams

       -sfx[{name}]
              Create SFX archive

       -so    Write data to stdout (e.g. 7z x -so directory.tar.7z | tar xf -)

       -spd   Disable wildcard matching for file names

       -spe   Eliminate duplication of root folder for extract command

       -spf   Use fully qualified file paths

       -ssc[-]
              Set sensitive case mode

       -ssw   Compress shared files

       -stl   Set archive timestamp from the most recently modified file

       -stm{HexMask}
              Set CPU thread affinity mask (hexadecimal number)

       -stx{Type}
              Exclude archive type

       -t{Type}
              Set type of archive

       -u[-][p#][q#][r#][x#][y#][z#][!newArchiveName]
              Update options

       -v{Size}[b|k|m|g]
              Create volumes

       -w[path]
              Set working directory. Empty path means a temporary directory

       -x[r[-|0]]]{@listfile|!wildcard}
              Exclude filenames

       -y     Assume Yes on all queries

DIAGNOSTICS
       7-Zip returns the following exit codes:

              0      Normal (no errors or warnings detected)

              1      Warning (Non fatal error(s)). For example, some files cannot be read during  compress‐
                     ing, so they were not compressed

              2      Fatal error

              7      Bad command line parameters

              8      Not enough memory for operation

              255    User stopped the process with control-C (or similar)

Backup and limitations
       DO NOT USE the 7-zip format for backup purpose on Linux/Unix because :
        - 7-zip does not store the owner/group of the file.

       On Linux/Unix, in order to backup directories you must use tar :
        - to backup a directory  : tar cf - directory | 7z a -si directory.tar.7z
        - to restore your backup : 7z x -so directory.tar.7z | tar xf -

       If  you  want  to  send  files  and directories (not the owner of file) to others Unix/MacOS/Windows
       users, you can use the 7-zip format.

         example : 7z a directory.7z  directory

       Do not use "-r" because this flag does not do what you think.

       Do not use directory/* because of ".*"  files  (example  :  "directory/*"  does  not  match  "direc‐
       tory/.profile")

EXAMPLE 1
       7z a -t7z -m0=lzma -mx=9 -mfb=64 -md=32m -ms=on archive.7z dir1
              adds all files from directory "dir1" to archive archive.7z using "ultra settings"

       -t7z   7z archive

       -m0=lzma
              lzma method

       -mx=9  level of compression = 9 (Ultra)

       -mfb=64
              number of fast bytes for LZMA = 64

       -md=32m
              dictionary size = 32 megabytes

       -ms=on solid archive = on

EXAMPLE 2
       7z a -sfx archive.exe dir1
              add all files from directory "dir1" to SFX archive archive.exe (Remark : SFX archive MUST end
              with ".exe")

EXAMPLE 3
       7z a -mhe=on -pmy_password archive.7z a_directory
              add all files from directory "a_directory" to the archive "archive.7z" (with data and  header
              archive encryption on)

SEE ALSO
       7zr(1), 7za(1), p7zip(1), bzip2(1), gzip(1), zip(1),

HTML Documentation
       /usr/share/doc/p7zip-full/DOC/MANUAL/start.htm

AUTHOR
       Written for Debian by Mohammed Adnene Trojette. Updated by Robert Luberda.

7-Zip                                         March 6th, 2016                                         7z(1)

## tldr 7z
7z

[0m[0mFile archiver with a high compression ratio.
More information: https://manned.org/7z.

 - [0m[32;23;22;24;25m[a]dd a file or directory to a new or existing archive:
   [33;23;22;24;25m7z a [0mpath/to/archive.7z[33;23;22;24;25m [0mpath/to/file_or_directory
[0m
 - [0m[32;23;22;24;25mEncrypt an existing archive (including filenames):
   [33;23;22;24;25m7z a [0mpath/to/encrypted.7z[33;23;22;24;25m -p[0mpassword[33;23;22;24;25m -mhe=on [0mpath/to/archive.7z
[0m
 - [0m[32;23;22;24;25mE[x]tract an archive preserving the original directory structure:
   [33;23;22;24;25m7z x [0mpath/to/archive.7z
[0m
 - [0m[32;23;22;24;25mE[x]tract an archive to a specific directory:
   [33;23;22;24;25m7z x [0mpath/to/archive.7z[33;23;22;24;25m -o[0mpath/to/output
[0m
 - [0m[32;23;22;24;25mE[x]tract an archive to stdout:
   [33;23;22;24;25m7z x [0mpath/to/archive.7z[33;23;22;24;25m -so[0m
[0m
 - [0m[32;23;22;24;25m[a]rchive using a specific archive type:
   [33;23;22;24;25m7z a -t[0m7z|bzip2|gzip|lzip|tar|zip[33;23;22;24;25m [0mpath/to/archive[33;23;22;24;25m [0mpath/to/file_or_directory
[0m
 - [0m[32;23;22;24;25m[l]ist the contents of an archive:
   [33;23;22;24;25m7z l [0mpath/to/archive.7z
[0m
 - [0m[32;23;22;24;25mSet the level of compression (higher means more compression, but slower):
   [33;23;22;24;25m7z a [0mpath/to/archive.7z[33;23;22;24;25m -mx=[0m0|1|3|5|7|9[33;23;22;24;25m [0mpath/to/file_or_directory
[0m[0m

# add-apt-repository

## man add-apt-repository
add-apt-repository(1)                     General Commands Manual                     add-apt-repository(1)

NAME
       add-apt-repository  - Adds a repository into the /etc/apt/sources.list or /etc/apt/sources.list.d or
       removes an existing one

SYNOPSIS
       add-apt-repository [OPTIONS] [LINE]

DESCRIPTION
       add-apt-repository is a script which adds an external APT repository to either /etc/apt/sources.list
       or a file in /etc/apt/sources.list.d/ or removes an already existing repository.

OPTIONS
       Note  that the --list, --ppa, --cloud, --uri, --sourceslist, and LINE parameters are mutually exclu‐
       sive; only one (or none) of them may be specified.

       -h, --help
              Show help message and exit.

       -d, --debug
              Print debug information to the command line.

       -r, --remove
              Remove the specified repository.

              This first will disable (comment out) the matching line(s), and then any modified file(s) un‐
              der sources.list.d/ will be removed if they contain only empty and commented lines.

              Note that this performs differently when used with the --enable-source and/or --component pa‐
              rameters.  Without either of those parameters, this removes the specified repository, includ‐
              ing  any deb-src line(s), and all components.  If --enable-source is used, this disables only
              the 'deb-src' line(s).  If --component is used, this removes only the specified component(s),
              and only removes the repository if no components remain.

              If  both  --enable-source  and  --component are used with --remove, the actions are performed
              separately: the specified component(s) will be removed from both deb and deb-src  lines,  and
              deb-src lines will be disabled.

       -y, --yes
              Assume yes to all queries.

       -n, --no-update
              After adding the repository, do not update the package cache.

       -l, --login
              Login to Launchpad (this is only needed for private PPAs).

       -s, --enable-source
              Allow downloading of the source packages from the repository.

              This adds and enables a 'deb-src' line for the repository.

              If  this parameter is used without any repository, it will enable all currently existing dis‐
              abled source repository (deb-src) entries that have a corresponding enabled binary repository
              (deb) entry.

              If  this  parameter  is  used  twice  without any repository, it will also add missing source
              repository entries for all existing binary repository (deb) entries.

       -c, --component
              Which component(s) should be used with the specified repository.

              If not specified, this will default to main.  This may be used multiple times to specify mul‐
              tiple components.

              If  this is used without any repository, it will add the component(s) to all currently exist‐
              ing (enabled) repositories, but only if listed in the main sources.list file.

       -p, --pocket
              What pocket to use.

              Defaults to none, which is equivalent to the release pocket.

              If this is used without any repository, it will add the  pocket  to  all  currently  existing
              repositories,  but  only  if listed in the main sources.list file. It will use the components
              currently configured with the release pocket, or if that is not currently configured, it will
              use the main and restricted components.

       --dry-run
              Show what would be done, but don't make any changes.

       -L, --list
              List currently configured repositories.

              This will only list enabled repositories; it will not show disabled repository lines.

              By default, this shows only binary (deb) repositories.  If --enable-source is also used, this
              will also show source (deb-src) repositories.

       -P, --ppa
              Add an Ubuntu Launchpad Personal Package Archive.

              Must be in the format ppa:USER/PPA, USER/PPA, or USER.

              The USER parameter should be the Launchpad team or person that owns the PPA.  The PPA parame‐
              ter should be the name of the PPA; if not provided, it defaults to 'ppa'.

              The GPG public key of the PPA will also be downloaded and added to apt's keyring.

              To add a private PPA, you must also use the --login parameter, and of course you must also be
              subscribed to the private PPA.

       -C, --cloud
              Add an Ubuntu Cloud Archive.

              Must be in the format cloud-archive:CANAME, uca:CANAME, or CANAME.

              The CANAME parameter should be the name of the Cloud Archive.  The CANAME parameter  may  op‐
              tionally be suffixed with the pocket, as either -updates or -proposed.  If not specified, the
              pocket defaults to -updates.

       -U, --uri
              Add an archive, specified as a single URI.

              If the URI provided is detected to be a PPA, this will operate as if the --ppa parameter  was
              used.

       -S, --sourceslist
              Add an archive, specified as a full source entry line in one-line sources.list format.

              This must follow the ONE-LINE-STYLE format as described in the sources.list manpage.

              If  the URI provided is detected to be a PPA, this will operate as if the --ppa parameter was
              used.

LINE
       LINE is a deprecated method to specify the repository to add/remove,  provided  only  for  backwards
       compatibility.   It  can be specified in any of the supported formats: sources.list line, plain uri,
       ppa shortcut, or cloud-archive shortcut.  It can also be specified  as  one  or  more  valid  compo‐
       nent(s).  The script will attempt to detect which format is provided.

       This  is not recommended as the autodetection of which line format is intended can be ambiguous, but
       older scripts may still use this method of specifying the repository.

       One special case of LINE is providing the value -, which will then read the LINE from stdin.

EXAMPLES
       add-apt-repository -P ppa:user/repository

       add-apt-repository -P user/repository

       add-apt-repository -C cloud-archive:queens

       add-apt-repository -C uca:queens

       add-apt-repository -C queens

       add-apt-repository -S 'deb http://myserver/path/to/repo stable main'

       add-apt-repository -S deb http://myserver/path/to/repo stable main

       add-apt-repository -U http://myserver/path/to/repo -c main

       add-apt-repository -U https://packages.medibuntu.org -c free -c non-free

       add-apt-repository -U http://extras.ubuntu.com/ubuntu

       add-apt-repository -s

       add-apt-repository -L

       add-apt-repository -s -r

       add-apt-repository -c universe

       add-apt-repository -r -c multiverse

DEPRECATED EXAMPLES
       add-apt-repository deb http://myserver/path/to/repo stable main

       add-apt-repository http://myserver/path/to/repo main

       add-apt-repository https://packages.medibuntu.org free non-free

       add-apt-repository http://extras.ubuntu.com/ubuntu

       add-apt-repository multiverse

SEE ALSO
       sources.list(5) apt-get(8)

COPYRIGHT
       This manual page was written by Chow Loong Jin <hyperair@gmail.com> for the Debian system  (but  may
       be  used by others). Permission is granted to copy, distribute and/or modify this document under the
       terms of the GNU General Public License, Version 2 or any later version published by the Free  Soft‐
       ware Foundation.

       On  Debian  systems,  the  complete  text  of  the  GNU  General  Public  License  can  be  found in
       /usr/share/common-licenses.

                                                                                      add-apt-repository(1)

## tldr add-apt-repository
add-apt-repository

[0m[0mManage apt repository definitions.
More information: https://manned.org/add-apt-repository.

 - [0m[32;23;22;24;25mAdd a new apt repository:
   [33;23;22;24;25madd-apt-repository [0mrepository_spec
[0m
 - [0m[32;23;22;24;25mRemove an apt repository:
   [33;23;22;24;25madd-apt-repository [0m[-r|--remove][33;23;22;24;25m [0mrepository_spec
[0m
 - [0m[32;23;22;24;25mUpdate the package cache after adding a repository:
   [33;23;22;24;25madd-apt-repository --update [0mrepository_spec
[0m
 - [0m[32;23;22;24;25mAllow source packages to be downloaded from the repository:
   [33;23;22;24;25madd-apt-repository [0m[-s|--enable-source][33;23;22;24;25m [0mrepository_spec
[0m[0m

# addpart

## man addpart
ADDPART(8)                                 System Administration                                 ADDPART(8)

NAME
       addpart - tell the kernel about the existence of a partition

SYNOPSIS
       addpart device partition start length

DESCRIPTION
       addpart tells the Linux kernel about the existence of the specified partition. The command is a
       simple wrapper around the "add partition" ioctl.

       This command doesn’t manipulate partitions on a block device.

PARAMETERS
       device
           The disk device.

       partition
           The partition number.

       start
           The beginning of the partition (in 512-byte sectors).

       length
           The length of the partition (in 512-byte sectors).

       -h, --help
           Display help text and exit.

       -V, --version
           Print version and exit.

SEE ALSO
       delpart(8), fdisk(8), parted(8), partprobe(8), partx(8)

REPORTING BUGS
       For bug reports, use the issue tracker at https://github.com/util-linux/util-linux/issues.

AVAILABILITY
       The addpart command is part of the util-linux package which can be downloaded from Linux Kernel
       Archive <https://www.kernel.org/pub/linux/utils/util-linux/>.

util-linux 2.38.1                                2022-05-11                                      ADDPART(8)

## tldr addpart

[0m[0mTell the Linux kernel about the existence of the specified partition.
A simple wrapper around the add partition ioctl.
More information: https://manned.org/addpart.

 - [0m[32;23;22;24;25mTell the kernel about the existence of the specified partition:
   [33;23;22;24;25maddpart [0mdevice[33;23;22;24;25m [0mpartition[33;23;22;24;25m [0mstart[33;23;22;24;25m [0mlength
[0m[0m

# alias

## man alias
NO INFO

## tldr alias
alias

[0m[0mCreate aliases - words that are replaced by a command string.
Aliases expire with the current shell session unless defined in the shell's configuration file, e.g. ~/.bashrc for Bash or ~/.zshrc for Zsh.
See also: unalias.
More information: https://www.gnu.org/software/bash/manual/bash.html#index-alias.

 - [0m[32;23;22;24;25mList all aliases:
   [33;23;22;24;25malias[0m
[0m
 - [0m[32;23;22;24;25mCreate a generic alias:
   [33;23;22;24;25malias [0mword[33;23;22;24;25m="[0mcommand[33;23;22;24;25m"[0m
[0m
 - [0m[32;23;22;24;25mView the command associated to a given alias:
   [33;23;22;24;25malias [0mword
[0m
 - [0m[32;23;22;24;25mRemove an aliased command:
   [33;23;22;24;25munalias [0mword
[0m
 - [0m[32;23;22;24;25mTurn rm into an interactive command:
   [33;23;22;24;25malias [0mrm[33;23;22;24;25m="[0mrm --interactive[33;23;22;24;25m"[0m
[0m
 - [0m[32;23;22;24;25mCreate la as a shortcut for ls --all:
   [33;23;22;24;25malias [0mla[33;23;22;24;25m="[0mls --all[33;23;22;24;25m"[0m
[0m[0m