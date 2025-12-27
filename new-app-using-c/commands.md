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

# apt

## man apt
APT(8)                                              APT                                              APT(8)

NAME
       apt - command-line interface

SYNOPSIS
       apt [-h] [-o=config_string] [-c=config_file] [-t=target_release] [-a=architecture] {list | search |
           show | update | install pkg [{=pkg_version_number | /target_release}]...  | remove pkg...  |
           upgrade | full-upgrade | edit-sources | {-v | --version} | {-h | --help}}

DESCRIPTION
       apt provides a high-level commandline interface for the package management system. It is intended as
       an end user interface and enables some options better suited for interactive usage by default
       compared to more specialized APT tools like apt-get(8) and apt-cache(8).

       Much like apt itself, its manpage is intended as an end user interface and as such only mentions the
       most used commands and options partly to not duplicate information in multiple places and partly to
       avoid overwhelming readers with a cornucopia of options and details.

       update (apt-get(8))
           update is used to download package information from all configured sources. Other commands
           operate on this data to e.g. perform package upgrades or search in and display details about all
           packages available for installation.

       upgrade (apt-get(8))
           upgrade is used to install available upgrades of all packages currently installed on the system
           from the sources configured via sources.list(5). New packages will be installed if required to
           satisfy dependencies, but existing packages will never be removed. If an upgrade for a package
           requires the removal of an installed package the upgrade for this package isn't performed.

       full-upgrade (apt-get(8))
           full-upgrade performs the function of upgrade but will remove currently installed packages if
           this is needed to upgrade the system as a whole.

       install, reinstall, remove, purge (apt-get(8))
           Performs the requested action on one or more packages specified via regex(7), glob(7) or exact
           match. The requested action can be overridden for specific packages by appending a plus (+) to
           the package name to install this package or a minus (-) to remove it.

           A specific version of a package can be selected for installation by following the package name
           with an equals (=) and the version of the package to select. Alternatively the version from a
           specific release can be selected by following the package name with a forward slash (/) and
           codename (bookworm, trixie, sid ...) or suite name (stable, testing, unstable). This will also
           select versions from this release for dependencies of this package if needed to satisfy the
           request.

           Removing a package removes all packaged data, but leaves usually small (modified) user
           configuration files behind, in case the remove was an accident. Just issuing an installation
           request for the accidentally removed package will restore its function as before in that case.
           On the other hand you can get rid of these leftovers by calling purge even on already removed
           packages. Note that this does not affect any data or configuration stored in your home
           directory.

       autoremove (apt-get(8))
           autoremove is used to remove packages that were automatically installed to satisfy dependencies
           for other packages and are now no longer needed as dependencies changed or the package(s)
           needing them were removed in the meantime.

           You should check that the list does not include applications you have grown to like even though
           they were once installed just as a dependency of another package. You can mark such a package as
           manually installed by using apt-mark(8). Packages which you have installed explicitly via
           install are also never proposed for automatic removal.

       satisfy (apt-get(8))
           satisfy satisfies dependency strings, as used in Build-Depends. It also handles conflicts, by
           prefixing an argument with "Conflicts: ".

           Example: apt satisfy "foo, bar (>= 1.0)" "Conflicts: baz, fuzz"

       search (apt-cache(8))
           search can be used to search for the given regex(7) term(s) in the list of available packages
           and display matches. This can e.g. be useful if you are looking for packages having a specific
           feature. If you are looking for a package including a specific file try apt-file(1).

       show (apt-cache(8))
           Show information about the given package(s) including its dependencies, installation and
           download size, sources the package is available from, the description of the packages content
           and much more. It can e.g. be helpful to look at this information before allowing apt(8) to
           remove a package or while searching for new packages to install.

       list
           list is somewhat similar to dpkg-query --list in that it can display a list of packages
           satisfying certain criteria. It supports glob(7) patterns for matching package names as well as
           options to list installed (--installed), upgradeable (--upgradeable) or all available
           (--all-versions) versions.

       edit-sources (work-in-progress)
           edit-sources lets you edit your sources.list(5) files in your preferred text editor while also
           providing basic sanity checks.

SCRIPT USAGE AND DIFFERENCES FROM OTHER APT TOOLS
       The apt(8) commandline is designed as an end-user tool and it may change behavior between versions.
       While it tries not to break backward compatibility this is not guaranteed either if a change seems
       beneficial for interactive use.

       All features of apt(8) are available in dedicated APT tools like apt-get(8) and apt-cache(8) as
       well.  apt(8) just changes the default value of some options (see apt.conf(5) and specifically the
       Binary scope). So you should prefer using these commands (potentially with some additional options
       enabled) in your scripts as they keep backward compatibility as much as possible.

SEE ALSO
       apt-get(8), apt-cache(8), sources.list(5), apt.conf(5), apt-config(8), The APT User's guide in
       /usr/share/doc/apt-doc/, apt_preferences(5), the APT Howto.

DIAGNOSTICS
       apt returns zero on normal operation, decimal 100 on error.

BUGS
       APT bug page[1]. If you wish to report a bug in APT, please see
       /usr/share/doc/debian/bug-reporting.txt or the reportbug(1) command.

AUTHOR
       APT team

NOTES
        1. APT bug page
           http://bugs.debian.org/src:apt

APT 2.6.1                                      05 April 2020                                         APT(8)

## tldr apt
apt

[0m[0mPackage manager for Debian-based distributions.
Intended as a user-friendly alternative to apt-get for interactive use.
For equivalent commands in other package managers, see https://wiki.archlinux.org/title/Pacman/Rosetta.
More information: https://manned.org/apt.8.

 - [0m[32;23;22;24;25mUpdate the list of available packages and versions (recommended before running other apt commands):
   [33;23;22;24;25msudo apt update[0m
[0m
 - [0m[32;23;22;24;25mSearch packages by name or description:
   [33;23;22;24;25mapt search [0mpackage
[0m
 - [0m[32;23;22;24;25mSearch packages by name only (supports wildcards like *):
   [33;23;22;24;25mapt list [0mpackage
[0m
 - [0m[32;23;22;24;25mShow detailed information about a package:
   [33;23;22;24;25mapt show [0mpackage
[0m
 - [0m[32;23;22;24;25mInstall a package, or update it to the latest version:
   [33;23;22;24;25msudo apt install [0mpackage
[0m
 - [0m[32;23;22;24;25mRemove a package (use purge instead to also remove configuration files):
   [33;23;22;24;25msudo apt remove [0mpackage
[0m
 - [0m[32;23;22;24;25mUpgrade all installed packages to their latest versions:
   [33;23;22;24;25msudo apt upgrade[0m
[0m
 - [0m[32;23;22;24;25mList all installed packages:
   [33;23;22;24;25mapt list [0m[-i|--installed]
[0m[0m

# apt-cache

## man apt-cache
APT-CACHE(8)                                        APT                                        APT-CACHE(8)

NAME
       apt-cache - query the APT cache

SYNOPSIS
       apt-cache [-agipns] [-o=config_string] [-c=config_file] {gencaches | showpkg pkg...  |
                 showsrc pkg...  | stats | dump | dumpavail | unmet | search regex...  |
                 show pkg [{=pkg_version_number | /target_release}]...  |
                 depends pkg [{=pkg_version_number | /target_release}]...  |
                 rdepends pkg [{=pkg_version_number | /target_release}]...  | pkgnames [prefix]  |
                 dotty pkg [{=pkg_version_number | /target_release}]...  |
                 xvcg pkg [{=pkg_version_number | /target_release}]...  | policy [pkg...]  | madison pkg...
                 | {-v | --version} | {-h | --help}}

DESCRIPTION
       apt-cache performs a variety of operations on APT's package cache.  apt-cache does not manipulate
       the state of the system but does provide operations to search and generate interesting output from
       the package metadata. The metadata is acquired and updated via the 'update' command of e.g.
       apt-get, so that it can be outdated if the last update is too long ago, but in exchange apt-cache
       works independently of the availability of the configured sources (e.g. offline).

       Unless the -h, or --help option is given, one of the commands below must be present.

       gencaches
           gencaches creates APT's package cache. This is done implicitly by all commands needing this
           cache if it is missing or outdated.

       showpkg pkg...
           showpkg displays information about the packages listed on the command line. Remaining arguments
           are package names. The available versions and reverse dependencies of each package listed are
           listed, as well as forward dependencies for each version. Forward (normal) dependencies are
           those packages upon which the package in question depends; reverse dependencies are those
           packages that depend upon the package in question. Thus, forward dependencies must be satisfied
           for a package, but reverse dependencies need not be. For instance, apt-cache showpkg
           libreadline2 would produce output similar to the following:

               Package: libreadline2
               Versions: 2.1-12(/var/state/apt/lists/foo_Packages),
               Reverse Depends:
                 libreadlineg2,libreadline2
                 libreadline2-altdev,libreadline2
               Dependencies:
               2.1-12 - libc5 (2 5.4.0-0) ncurses3.0 (0 (null))
               Provides:
               2.1-12 -
               Reverse Provides:
           Thus it may be seen that libreadline2, version 2.1-12, depends on libc5 and ncurses3.0 which
           must be installed for libreadline2 to work. In turn, libreadlineg2 and libreadline2-altdev
           depend on libreadline2. If libreadline2 is installed, libc5 and ncurses3.0 (and ldso) must also
           be installed; libreadlineg2 and libreadline2-altdev do not have to be installed. For the
           specific meaning of the remainder of the output it is best to consult the apt source code.

       stats
           stats displays some statistics about the cache. No further arguments are expected. Statistics
           reported are:

           •   Total package names is the number of package names found in the cache.

           •   Normal packages is the number of regular, ordinary package names; these are packages that
               bear a one-to-one correspondence between their names and the names used by other packages
               for them in dependencies. The majority of packages fall into this category.

           •   Pure virtual packages is the number of packages that exist only as a virtual package name;
               that is, packages only "provide" the virtual package name, and no package actually uses the
               name. For instance, "mail-transport-agent" in the Debian system is a pure virtual package;
               several packages provide "mail-transport-agent", but there is no package named
               "mail-transport-agent".

           •   Single virtual packages is the number of packages with only one package providing a
               particular virtual package. For example, in the Debian system, "X11-text-viewer" is a
               virtual package, but only one package, xless, provides "X11-text-viewer".

           •   Mixed virtual packages is the number of packages that either provide a particular virtual
               package or have the virtual package name as the package name. For instance, in the Debian
               system, "debconf" is both an actual package, and provided by the debconf-tiny package.

           •   Missing is the number of package names that were referenced in a dependency but were not
               provided by any package. Missing packages may be an evidence if a full distribution is not
               accessed, or if a package (real or virtual) has been dropped from the distribution. Usually
               they are referenced from Conflicts or Breaks statements.

           •   Total distinct versions is the number of package versions found in the cache. If more than
               one distribution is being accessed (for instance, "stable" and "unstable"), this value can
               be considerably larger than the number of total package names.

           •   Total dependencies is the number of dependency relationships claimed by all of the packages
               in the cache.

       showsrc pkg...
           showsrc displays all the source package records that match the given package names. All versions
           are shown, as well as all records that declare the name to be a binary package. Use
           --only-source to display only source package names.

       dump
           dump shows a short listing of every package in the cache. It is primarily for debugging.

       dumpavail
           dumpavail prints out an available list to stdout. This is suitable for use with dpkg(1) and is
           used by the dselect(1) method.

       unmet
           unmet displays a summary of all unmet dependencies in the package cache.

       show pkg...
           show performs a function similar to dpkg --print-avail; it displays the package records for the
           named packages.

       search regex...
           search performs a full text search on all available package lists for the POSIX regex pattern
           given, see regex(7). It searches the package names and the descriptions for an occurrence of the
           regular expression and prints out the package name and the short description, including virtual
           package names. If --full is given then output identical to show is produced for each matched
           package, and if --names-only is given then the long description is not searched, only the
           package name and provided packages are.

           Separate arguments can be used to specify multiple search patterns that are and'ed together.

       depends pkg...
           depends shows a listing of each dependency a package has and all the possible other packages
           that can fulfill that dependency.

       rdepends pkg...
           rdepends shows a listing of each reverse dependency a package has.

       pkgnames [prefix]
           This command prints the name of each package APT knows. The optional argument is a prefix match
           to filter the name list. The output is suitable for use in a shell tab complete function and the
           output is generated extremely quickly. This command is best used with the --generate option.

           Note that a package which APT knows of is not necessarily available to download, installable or
           installed, e.g. virtual packages are also listed in the generated list.

       dotty pkg...
           dotty takes a list of packages on the command line and generates output suitable for use by
           dotty from the GraphViz[1] package. The result will be a set of nodes and edges representing the
           relationships between the packages. By default the given packages will trace out all dependent
           packages; this can produce a very large graph. To limit the output to only the packages listed
           on the command line, set the APT::Cache::GivenOnly option.

           The resulting nodes will have several shapes; normal packages are boxes, pure virtual packages
           are triangles, mixed virtual packages are diamonds, missing packages are hexagons. Orange boxes
           mean recursion was stopped (leaf packages), blue lines are pre-depends, green lines are
           conflicts.

           Caution, dotty cannot graph larger sets of packages.

       xvcg pkg...
           The same as dotty, only for xvcg from the VCG tool[2].

       policy [pkg...]
           policy is meant to help debug issues relating to the preferences file. With no arguments it will
           print out the priorities of each source. Otherwise it prints out detailed information about the
           priority selection of the named package.

       madison pkg...
           apt-cache's madison command attempts to mimic the output format and a subset of the
           functionality of the Debian archive management tool, madison. It displays available versions of
           a package in a tabular format. Unlike the original madison, it can only display information for
           the architecture for which APT has retrieved package lists (APT::Architecture).

OPTIONS
       All command line options may be set using the configuration file, the descriptions indicate the
       configuration option to set. For boolean options you can override the config file by using something
       like -f-,--no-f, -f=no or several other variations.

       -p, --pkg-cache
           Select the file to store the package cache. The package cache is the primary cache used by all
           operations. Configuration Item: Dir::Cache::pkgcache.

       -s, --src-cache
           Select the file to store the source cache. The source is used only by gencaches and it stores a
           parsed version of the package information from remote sources. When building the package cache
           the source cache is used to avoid reparsing all of the package files. Configuration Item:
           Dir::Cache::srcpkgcache.

       -q, --quiet
           Quiet; produces output suitable for logging, omitting progress indicators. More q's will produce
           more quietness up to a maximum of 2. You can also use -q=# to set the quietness level,
           overriding the configuration file. Configuration Item: quiet.

       -i, --important
           Print only important dependencies; for use with unmet and depends. Causes only Depends and
           Pre-Depends relations to be printed. Configuration Item: APT::Cache::Important.

       --no-pre-depends, --no-depends, --no-recommends, --no-suggests, --no-conflicts, --no-breaks,
       --no-replaces, --no-enhances
           Per default the depends and rdepends print all dependencies. This can be tweaked with these
           flags which will omit the specified dependency type. Configuration Item:
           APT::Cache::ShowDependencyType e.g.  APT::Cache::ShowRecommends.

       --implicit
           Per default depends and rdepends print only dependencies explicitly expressed in the metadata.
           With this flag it will also show dependencies implicitly added based on the encountered data. A
           Conflicts: foo e.g. expresses implicitly that this package also conflicts with the package foo
           from any other architecture. Configuration Item: APT::Cache::ShowImplicit.

       -f, --full
           Print full package records when searching. Configuration Item: APT::Cache::ShowFull.

       -a, --all-versions
           Print full records for all available versions. This is the default; to turn it off, use
           --no-all-versions. If --no-all-versions is specified, only the candidate version will be
           displayed (the one which would be selected for installation). This option is only applicable to
           the show command. Configuration Item: APT::Cache::AllVersions.

       -g, --generate
           Perform automatic package cache regeneration, rather than use the cache as it is. This is the
           default; to turn it off, use --no-generate. Configuration Item: APT::Cache::Generate.

       --names-only, -n
           Only search on the package and provided package names, not the long descriptions. Configuration
           Item: APT::Cache::NamesOnly.

       --all-names
           Make pkgnames print all names, including virtual packages and missing dependencies.
           Configuration Item: APT::Cache::AllNames.

       --recurse
           Make depends and rdepends recursive so that all packages mentioned are printed once.
           Configuration Item: APT::Cache::RecurseDepends.

       --installed
           Limit the output of depends and rdepends to packages which are currently installed.
           Configuration Item: APT::Cache::Installed.

       --with-source filename
           Adds the given file as a source for metadata. Can be repeated to add multiple files. Supported
           are currently *.deb, *.dsc, *.changes, Sources and Packages files as well as source package
           directories. Files are matched based on their name only, not their content!

           Sources and Packages can be compressed in any format apt supports as long as they have the
           correct extension. If you need to store multiple of these files in one directory you can prefix
           a name of your choice with the last character being an underscore ("_"). Example:
           my.example_Packages.xz

           Note that these sources are treated as trusted (see apt-secure(8)). Configuration Item:
           APT::Sources::With.

       -h, --help
           Show a short usage summary.

       -v, --version
           Show the program version.

       -c, --config-file
           Configuration File; Specify a configuration file to use. The program will read the default
           configuration file and then this configuration file. If configuration settings need to be set
           before the default configuration files are parsed specify a file with the APT_CONFIG environment
           variable. See apt.conf(5) for syntax information.

       -o, --option
           Set a Configuration Option; This will set an arbitrary configuration option. The syntax is -o
           Foo::Bar=bar.  -o and --option can be used multiple times to set different options.

FILES
       /etc/apt/sources.list
           Locations to fetch packages from. Configuration Item: Dir::Etc::SourceList.

       /etc/apt/sources.list.d/
           File fragments for locations to fetch packages from. Configuration Item: Dir::Etc::SourceParts.

       /var/lib/apt/lists/
           Storage area for state information for each package resource specified in sources.list(5)
           Configuration Item: Dir::State::Lists.

       /var/lib/apt/lists/partial/
           Storage area for state information in transit. Configuration Item: Dir::State::Lists (partial
           will be implicitly appended)

SEE ALSO
       apt.conf(5), sources.list(5), apt-get(8)

DIAGNOSTICS
       apt-cache returns zero on normal operation, decimal 100 on error.

BUGS
       APT bug page[3]. If you wish to report a bug in APT, please see
       /usr/share/doc/debian/bug-reporting.txt or the reportbug(1) command.

AUTHORS
       Jason Gunthorpe

       APT team

NOTES
        1. GraphViz
           http://www.research.att.com/sw/tools/graphviz/

        2. VCG tool
           http://rw4.cs.uni-sb.de/users/sander/html/gsvcg1.html

        3. APT bug page
           http://bugs.debian.org/src:apt

APT 2.6.1                                      04 April 2019                                   APT-CACHE(8)

## tldr apt-cache
apt-cache

[0m[0mDebian and Ubuntu package query tool.
More information: https://manned.org/apt-cache.

 - [0m[32;23;22;24;25mSearch for a package in your current sources:
   [33;23;22;24;25mapt-cache search [0mquery
[0m
 - [0m[32;23;22;24;25mShow information about a package:
   [33;23;22;24;25mapt-cache show [0mpackage
[0m
 - [0m[32;23;22;24;25mShow whether a package is installed and up to date:
   [33;23;22;24;25mapt-cache policy [0mpackage
[0m
 - [0m[32;23;22;24;25mShow dependencies for a package:
   [33;23;22;24;25mapt-cache depends [0mpackage
[0m
 - [0m[32;23;22;24;25mShow packages that depend on a particular package:
   [33;23;22;24;25mapt-cache rdepends [0mpackage
[0m[0m

# apt-add-repository

## man apt-add-repository
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

## tldr apt-add-repository
apt-add-repository

[0m[0mThis command is an alias of add-apt-repository.

 - [0m[32;23;22;24;25mView documentation for the original command:
   [33;23;22;24;25mtldr add-apt-repository[0m
[0m[0m

# apt-cdrom

## man apt-cdrom
APT-CDROM(8)                                        APT                                        APT-CDROM(8)

NAME
       apt-cdrom - APT CD-ROM management utility

SYNOPSIS
       apt-cdrom [-rmfan] [-d=cdrom_mount_point] [-o=config_string] [-c=config_file] {add | ident |
                 {-v | --version} | {-h | --help}}

DESCRIPTION
       apt-cdrom is used to add a new CD-ROM to APT's list of available sources.  apt-cdrom takes care of
       determining the structure of the disc as well as correcting for several possible mis-burns and
       verifying the index files.

       It is necessary to use apt-cdrom to add CDs to the APT system; it cannot be done by hand.
       Furthermore each disc in a multi-CD set must be inserted and scanned separately to account for
       possible mis-burns.

       Unless the -h, or --help option is given, one of the commands below must be present.

       add
           add is used to add a new disc to the source list. It will unmount the CD-ROM device, prompt for
           a disc to be inserted and then proceed to scan it and copy the index files. If the disc does not
           have a proper .disk directory you will be prompted for a descriptive title.

           APT uses a CD-ROM ID to track which disc is currently in the drive and maintains a database of
           these IDs in /var/lib/apt/cdroms.list

       ident
           A debugging tool to report the identity of the current disc as well as the stored file name

OPTIONS
       All command line options may be set using the configuration file, the descriptions indicate the
       configuration option to set. For boolean options you can override the config file by using something
       like -f-,--no-f, -f=no or several other variations.

       --no-auto-detect, --cdrom
           Do not try to auto-detect the CD-ROM path. Usually combined with the --cdrom option.
           Configuration Item: Acquire::cdrom::AutoDetect.

       -d, --cdrom
           Mount point; specify the location to mount the CD-ROM. This mount point must be listed in
           /etc/fstab and properly configured. Configuration Item: Acquire::cdrom::mount.

       -r, --rename
           Rename a disc; change the label of a disc or override the disc's given label. This option will
           cause apt-cdrom to prompt for a new label. Configuration Item: APT::CDROM::Rename.

       -m, --no-mount
           No mounting; prevent apt-cdrom from mounting and unmounting the mount point. Configuration Item:
           APT::CDROM::NoMount.

       -f, --fast
           Fast Copy; Assume the package files are valid and do not check every package. This option should
           be used only if apt-cdrom has been run on this disc before and did not detect any errors.
           Configuration Item: APT::CDROM::Fast.

       -a, --thorough
           Thorough Package Scan; This option may be needed with some old Debian 1.1/1.2 discs that have
           Package files in strange places. It takes much longer to scan the CD but will pick them all up.

       -n, --just-print, --recon, --no-act
           No Changes; Do not change the sources.list(5) file and do not write index files. Everything is
           still checked however. Configuration Item: APT::CDROM::NoAct.

       -h, --help
           Show a short usage summary.

       -v, --version
           Show the program version.

       -c, --config-file
           Configuration File; Specify a configuration file to use. The program will read the default
           configuration file and then this configuration file. If configuration settings need to be set
           before the default configuration files are parsed specify a file with the APT_CONFIG environment
           variable. See apt.conf(5) for syntax information.

       -o, --option
           Set a Configuration Option; This will set an arbitrary configuration option. The syntax is -o
           Foo::Bar=bar.  -o and --option can be used multiple times to set different options.

SEE ALSO
       apt.conf(5), apt-get(8), sources.list(5)

DIAGNOSTICS
       apt-cdrom returns zero on normal operation, decimal 100 on error.

BUGS
       APT bug page[1]. If you wish to report a bug in APT, please see
       /usr/share/doc/debian/bug-reporting.txt or the reportbug(1) command.

AUTHORS
       Jason Gunthorpe

       APT team

NOTES
        1. APT bug page
           http://bugs.debian.org/src:apt

APT 2.6.1                                     30 November 2013                                 APT-CDROM(8)

## tldr apt-cdrom
NO INFORMATION

# apt-config

## man apt-config
APT-CONFIG(8)                                       APT                                       APT-CONFIG(8)

NAME
       apt-config - APT Configuration Query program

SYNOPSIS
       apt-config [--empty] [--format '%f "%v";%n'] [-o=config_string] [-c=config_file] {shell | dump |
                  {-v | --version} | {-h | --help}}

DESCRIPTION
       apt-config is an internal program used by various portions of the APT suite to provide consistent
       configurability. It accesses the main configuration file /etc/apt/apt.conf in a manner that is easy
       to use for scripted applications.

       Unless the -h, or --help option is given, one of the commands below must be present.

       shell
           shell is used to access the configuration information from a shell script. It is given pairs of
           arguments, the first being a shell variable and the second the configuration value to query. As
           output it lists shell assignment commands for each value present. In a shell script it should be
           used as follows:

               OPTS="-f"
               RES=`apt-config shell OPTS MyApp::options`
               eval $RES
           This will set the shell environment variable $OPTS to the value of MyApp::options with a default
           of -f.

           The configuration item may be postfixed with a /[fdbi]. f returns file names, d returns
           directories, b returns true or false and i returns an integer. Each of the returns is normalized
           and verified internally.

       dump
           Just show the contents of the configuration space.

OPTIONS
       All command line options may be set using the configuration file, the descriptions indicate the
       configuration option to set. For boolean options you can override the config file by using something
       like -f-,--no-f, -f=no or several other variations.

       --empty
           Include options which have an empty value. This is the default, so use --no-empty to remove them
           from the output.

       --format '%f "%v";%n'
           Defines the output of each config option. %t will be replaced with its individual name, %f with
           its full hierarchical name and %v with its value. Use uppercase letters and special characters
           in the value will be encoded to ensure that it can e.g. be safely used in a quoted-string as
           defined by RFC822. Additionally %n will be replaced by a newline, and %N by a tab. A % can be
           printed by using %%.

       -h, --help
           Show a short usage summary.

       -v, --version
           Show the program version.

       -c, --config-file
           Configuration File; Specify a configuration file to use. The program will read the default
           configuration file and then this configuration file. If configuration settings need to be set
           before the default configuration files are parsed specify a file with the APT_CONFIG environment
           variable. See apt.conf(5) for syntax information.

       -o, --option
           Set a Configuration Option; This will set an arbitrary configuration option. The syntax is -o
           Foo::Bar=bar.  -o and --option can be used multiple times to set different options.

SEE ALSO
       apt.conf(5)

DIAGNOSTICS
       apt-config returns zero on normal operation, decimal 100 on error.

BUGS
       APT bug page[1]. If you wish to report a bug in APT, please see
       /usr/share/doc/debian/bug-reporting.txt or the reportbug(1) command.

AUTHORS
       Jason Gunthorpe

       APT team

NOTES
        1. APT bug page
           http://bugs.debian.org/src:apt

APT 2.6.1                                     30 November 2013                                APT-CONFIG(8)

## tldr apt-config
NO INFORMATION

# apt-extracttemplates

## man apt-extracttemplates
APT-EXTRACTTEMPLATE(1)                              APT                              APT-EXTRACTTEMPLATE(1)

NAME
       apt-extracttemplates - Utility to extract debconf config and templates from Debian packages

SYNOPSIS
       apt-extracttemplates [-t=temporary_directory] filename... {-v | --version} {-h | --help}

DESCRIPTION
       apt-extracttemplates will take one or more Debian package files as input and write out (to a
       temporary directory) all associated config scripts and template files. For each passed in package
       that contains config scripts and templates, one line of output will be generated in the format:

       package version template-file config-script

       template-file and config-script are written to the temporary directory specified by the -t or
       --tempdir (APT::ExtractTemplates::TempDir) directory, with filenames of the form
       package.template.XXXXXX and package.config.XXXXXX

OPTIONS
       All command line options may be set using the configuration file, the descriptions indicate the
       configuration option to set. For boolean options you can override the config file by using something
       like -f-,--no-f, -f=no or several other variations.

       -t, --tempdir
           Temporary directory in which to write extracted debconf template files and config scripts.
           Configuration Item: APT::ExtractTemplates::TempDir

       -h, --help
           Show a short usage summary.

       -v, --version
           Show the program version.

       -c, --config-file
           Configuration File; Specify a configuration file to use. The program will read the default
           configuration file and then this configuration file. If configuration settings need to be set
           before the default configuration files are parsed specify a file with the APT_CONFIG environment
           variable. See apt.conf(5) for syntax information.

       -o, --option
           Set a Configuration Option; This will set an arbitrary configuration option. The syntax is -o
           Foo::Bar=bar.  -o and --option can be used multiple times to set different options.

SEE ALSO
       apt.conf(5)

DIAGNOSTICS
       apt-extracttemplates returns zero on normal operation, decimal 100 on error.

BUGS
       APT bug page[1]. If you wish to report a bug in APT, please see
       /usr/share/doc/debian/bug-reporting.txt or the reportbug(1) command.

AUTHORS
       Jason Gunthorpe

       APT team

NOTES
        1. APT bug page
           http://bugs.debian.org/src:apt

APT 2.6.1                                      27 March 2014                         APT-EXTRACTTEMPLATE(1)

## tldr apt-extracttemplates
NO INFORMATION

# apt-ftparchive

## man apt-ftparchive
APT-FTPARCHIVE(1)                                   APT                                   APT-FTPARCHIVE(1)

NAME
       apt-ftparchive - Utility to generate index files

SYNOPSIS
       apt-ftparchive [-dsq] [--md5] [--delink] [--readonly] [--contents] [--arch architecture]
                      [-o=config_string] [-c=config_file] {packages path [override-file [pathprefix]]  |
                      sources path [override-file [pathprefix]]  | contents path  | release path  |
                      generate config_file section...  | clean config_file  | {-v | --version} |
                      {-h | --help}}

DESCRIPTION
       apt-ftparchive is the command line tool that generates the index files that APT uses to access a
       distribution source. The index files should be generated on the origin site based on the content of
       that site.

       apt-ftparchive is a superset of the dpkg-scanpackages(1) program, incorporating its entire
       functionality via the packages command. It also contains a contents file generator, contents, and an
       elaborate means to 'script' the generation process for a complete archive.

       Internally apt-ftparchive can make use of binary databases to cache the contents of a .deb file and
       it does not rely on any external programs aside from gzip(1). When doing a full generate it
       automatically performs file-change checks and builds the desired compressed output files.

       Unless the -h, or --help option is given, one of the commands below must be present.

       packages
           The packages command generates a package file from a directory tree. It takes the given
           directory and recursively searches it for .deb files, emitting a package record to stdout for
           each. This command is approximately equivalent to dpkg-scanpackages(1).

           The option --db can be used to specify a binary caching DB.

       sources
           The sources command generates a source index file from a directory tree. It takes the given
           directory and recursively searches it for .dsc files, emitting a source record to stdout for
           each. This command is approximately equivalent to dpkg-scansources(1).

           If an override file is specified then a source override file will be looked for with an
           extension of .src. The --source-override option can be used to change the source override file
           that will be used.

       contents
           The contents command generates a contents file from a directory tree. It takes the given
           directory and recursively searches it for .deb files, and reads the file list from each file. It
           then sorts and writes to stdout the list of files matched to packages. Directories are not
           written to the output. If multiple packages own the same file then each package is separated by
           a comma in the output.

           The option --db can be used to specify a binary caching DB.

       release
           The release command generates a Release file from a directory tree. It recursively searches the
           given directory for uncompressed and compressed Packages, Sources, Contents, Components and
           icons files as well as Release, Index and md5sum.txt files by default
           (APT::FTPArchive::Release::Default-Patterns). Additional filename patterns can be added by
           listing them in APT::FTPArchive::Release::Patterns. It then writes to stdout a Release file
           containing (by default) an MD5, SHA1, SHA256 and SHA512 digest for each file.

           Values for the additional metadata fields in the Release file are taken from the corresponding
           variables under APT::FTPArchive::Release, e.g.  APT::FTPArchive::Release::Origin. The supported
           fields are Origin, Label, Suite, Version, Codename, Date, NotAutomatic, ButAutomaticUpgrades,
           Acquire-By-Hash, Valid-Until, Signed-By, Architectures, Components and Description.

       generate
           The generate command is designed to be runnable from a cron script and builds indexes according
           to the given config file. The config language provides a flexible means of specifying which
           index files are built from which directories, as well as providing a simple means of maintaining
           the required settings.

       clean
           The clean command tidies the databases used by the given configuration file by removing any
           records that are no longer necessary.

THE GENERATE CONFIGURATION
       The generate command uses a configuration file to describe the archives that are going to be
       generated. It follows the typical ISC configuration format as seen in ISC tools like bind 8 and
       dhcpd.  apt.conf(5) contains a description of the syntax. Note that the generate configuration is
       parsed in sectional manner, but apt.conf(5) is parsed in a tree manner. This only effects how the
       scope tag is handled.

       The generate configuration has four separate sections, each described below.

   Dir Section
       The Dir section defines the standard directories needed to locate the files required during the
       generation process. These directories are prepended certain relative paths defined in later sections
       to produce a complete an absolute path.

       ArchiveDir
           Specifies the root of the FTP archive, in a standard Debian configuration this is the directory
           that contains the ls-LR and dist nodes.

       OverrideDir
           Specifies the location of the override files.

       CacheDir
           Specifies the location of the cache files.

       FileListDir
           Specifies the location of the file list files, if the FileList setting is used below.

   Default Section
       The Default section specifies default values, and settings that control the operation of the
       generator. Other sections may override these defaults with a per-section setting.

       Packages::Compress
           Sets the default compression schemes to use for the package index files. It is a string that
           contains a space separated list of at least one of the compressors configured via the
           APT::Compressor configuration scope. The default for all compression schemes is '. gzip'.

       Packages::Extensions
           Sets the default list of file extensions that are package files. This defaults to '.deb'.

       Sources::Compress
           This is similar to Packages::Compress except that it controls the compression for the Sources
           files.

       Sources::Extensions
           Sets the default list of file extensions that are source files. This defaults to '.dsc'.

       Contents::Compress
           This is similar to Packages::Compress except that it controls the compression for the Contents
           files.

       Translation::Compress
           This is similar to Packages::Compress except that it controls the compression for the
           Translation-en master file.

       DeLinkLimit
           Specifies the number of kilobytes to delink (and replace with hard links) per run. This is used
           in conjunction with the per-section External-Links setting.

       FileMode
           Specifies the mode of all created index files. It defaults to 0644. All index files are set to
           this mode with no regard to the umask.

       LongDescription
           Specifies whether long descriptions should be included in the Packages file or split out into a
           master Translation-en file.

   TreeDefault Section
       Sets defaults specific to Tree sections. All of these variables are substitution variables and have
       the strings $(DIST), $(SECTION) and $(ARCH) replaced with their respective values.

       MaxContentsChange
           Sets the number of kilobytes of contents files that are generated each day. The contents files
           are round-robined so that over several days they will all be rebuilt.

       ContentsAge
           Controls the number of days a contents file is allowed to be checked without changing. If this
           limit is passed the mtime of the contents file is updated. This case can occur if the package
           file is changed in such a way that does not result in a new contents file [override edit for
           instance]. A hold off is allowed in hopes that new .debs will be installed, requiring a new file
           anyhow. The default is 10, the units are in days.

       Directory
           Sets the top of the .deb directory tree. Defaults to $(DIST)/$(SECTION)/binary-$(ARCH)/

       SrcDirectory
           Sets the top of the source package directory tree. Defaults to $(DIST)/$(SECTION)/source/

       Packages
           Sets the output Packages file. Defaults to $(DIST)/$(SECTION)/binary-$(ARCH)/Packages

       Sources
           Sets the output Sources file. Defaults to $(DIST)/$(SECTION)/source/Sources

       Translation
           Sets the output Translation-en master file with the long descriptions if they should be not
           included in the Packages file. Defaults to $(DIST)/$(SECTION)/i18n/Translation-en

       InternalPrefix
           Sets the path prefix that causes a symlink to be considered an internal link instead of an
           external link. Defaults to $(DIST)/$(SECTION)/

       Contents
           Sets the output Contents file. Defaults to $(DIST)/$(SECTION)/Contents-$(ARCH). If this setting
           causes multiple Packages files to map onto a single Contents file (as is the default) then
           apt-ftparchive will integrate those package files together automatically.

       Contents::Header
           Sets header file to prepend to the contents output.

       BinCacheDB
           Sets the binary cache database to use for this section. Multiple sections can share the same
           database.

       FileList
           Specifies that instead of walking the directory tree, apt-ftparchive should read the list of
           files from the given file. Relative files names are prefixed with the archive directory.

       SourceFileList
           Specifies that instead of walking the directory tree, apt-ftparchive should read the list of
           files from the given file. Relative files names are prefixed with the archive directory. This is
           used when processing source indexes.

   Tree Section
       The Tree section defines a standard Debian file tree which consists of a base directory, then
       multiple sections in that base directory and finally multiple Architectures in each section. The
       exact pathing used is defined by the Directory substitution variable.

       The Tree section takes a scope tag which sets the $(DIST) variable and defines the root of the tree
       (the path is prefixed by ArchiveDir). Typically this is a setting such as dists/bookworm.

       All of the settings defined in the TreeDefault section can be used in a Tree section as well as
       three new variables.

       When processing a Tree section apt-ftparchive performs an operation similar to:

           for i in Sections do
              for j in Architectures do
                 Generate for DIST=scope SECTION=i ARCH=j

       Sections
           This is a space separated list of sections which appear under the distribution; typically this
           is something like main contrib non-free non-free-firmware

       Architectures
           This is a space separated list of all the architectures that appear under search section. The
           special architecture 'source' is used to indicate that this tree has a source archive. The
           architecture 'all' signals that architecture specific files like Packages should not include
           information about architecture all packages in all files as they will be available in a
           dedicated file.

       LongDescription
           Specifies whether long descriptions should be included in the Packages file or split out into a
           master Translation-en file.

       BinOverride
           Sets the binary override file. The override file contains section, priority and maintainer
           address information.

       SrcOverride
           Sets the source override file. The override file contains section information.

       ExtraOverride
           Sets the binary extra override file.

       SrcExtraOverride
           Sets the source extra override file.

   BinDirectory Section
       The bindirectory section defines a binary directory tree with no special structure. The scope tag
       specifies the location of the binary directory and the settings are similar to the Tree section with
       no substitution variables or SectionArchitecture settings.

       Packages
           Sets the Packages file output.

       Sources
           Sets the Sources file output. At least one of Packages or Sources is required.

       Contents
           Sets the Contents file output (optional).

       BinOverride
           Sets the binary override file.

       SrcOverride
           Sets the source override file.

       ExtraOverride
           Sets the binary extra override file.

       SrcExtraOverride
           Sets the source extra override file.

       BinCacheDB
           Sets the cache DB.

       PathPrefix
           Appends a path to all the output paths.

       FileList, SourceFileList
           Specifies the file list file.

THE BINARY OVERRIDE FILE
       The binary override file is fully compatible with dpkg-scanpackages(1). It contains four fields
       separated by spaces. The first field is the package name, the second is the priority to force that
       package to, the third is the section to force that package to and the final field is the maintainer
       permutation field.

       The general form of the maintainer field is:

           old [// oldn]* => new

       or simply,

           new

       The first form allows a double-slash separated list of old email addresses to be specified. If any
       of those are found then new is substituted for the maintainer field. The second form unconditionally
       substitutes the maintainer field.

THE SOURCE OVERRIDE FILE
       The source override file is fully compatible with dpkg-scansources(1). It contains two fields
       separated by spaces. The first field is the source package name, the second is the section to assign
       it.

THE EXTRA OVERRIDE FILE
       The extra override file allows any arbitrary tag to be added or replaced in the output. It has three
       columns, the first is the package, the second is the tag and the remainder of the line is the new
       value.

OPTIONS
       All command line options may be set using the configuration file, the descriptions indicate the
       configuration option to set. For boolean options you can override the config file by using something
       like -f-,--no-f, -f=no or several other variations.

       --md5, --sha1, --sha256, --sha512
           Generate the given checksum. These options default to on, when turned off the generated index
           files will not have the checksum fields where possible. Configuration Items:
           APT::FTPArchive::Checksum and APT::FTPArchive::Index::Checksum where Index can be Packages,
           Sources or Release and Checksum can be MD5, SHA1, SHA256 or SHA512.

       -d, --db
           Use a binary caching DB. This has no effect on the generate command. Configuration Item:
           APT::FTPArchive::DB.

       -q, --quiet
           Quiet; produces output suitable for logging, omitting progress indicators. More q's will produce
           more quiet up to a maximum of 2. You can also use -q=# to set the quiet level, overriding the
           configuration file. Configuration Item: quiet.

       --delink
           Perform Delinking. If the External-Links setting is used then this option actually enables
           delinking of the files. It defaults to on and can be turned off with --no-delink. Configuration
           Item: APT::FTPArchive::DeLinkAct.

       --contents
           Perform contents generation. When this option is set and package indexes are being generated
           with a cache DB then the file listing will also be extracted and stored in the DB for later use.
           When using the generate command this option also allows the creation of any Contents files. The
           default is on. Configuration Item: APT::FTPArchive::Contents.

       -s, --source-override
           Select the source override file to use with the sources command. Configuration Item:
           APT::FTPArchive::SourceOverride.

       --readonly
           Make the caching databases read only. Configuration Item: APT::FTPArchive::ReadOnlyDB.

       -a, --arch
           Accept in the packages and contents commands only package files matching *_arch.deb or *_all.deb
           instead of all package files in the given path. Configuration Item:
           APT::FTPArchive::Architecture.

       APT::FTPArchive::AlwaysStat
           apt-ftparchive(1) caches as much as possible of metadata in a cachedb. If packages are
           recompiled and/or republished with the same version again, this will lead to problems as the now
           outdated cached metadata like size and checksums will be used. With this option enabled this
           will no longer happen as it will be checked if the file was changed. Note that this option is
           set to "false" by default as it is not recommend to upload multiple versions/builds of a package
           with the same version number, so in theory nobody will have these problems and therefore all
           these extra checks are useless.

       APT::FTPArchive::LongDescription
           This configuration option defaults to "true" and should only be set to "false" if the Archive
           generated with apt-ftparchive(1) also provides Translation files. Note that the Translation-en
           master file can only be created in the generate command.

       -h, --help
           Show a short usage summary.

       -v, --version
           Show the program version.

       -c, --config-file
           Configuration File; Specify a configuration file to use. The program will read the default
           configuration file and then this configuration file. If configuration settings need to be set
           before the default configuration files are parsed specify a file with the APT_CONFIG environment
           variable. See apt.conf(5) for syntax information.

       -o, --option
           Set a Configuration Option; This will set an arbitrary configuration option. The syntax is -o
           Foo::Bar=bar.  -o and --option can be used multiple times to set different options.

EXAMPLES
       To create a compressed Packages file for a directory containing binary packages (.deb):

           apt-ftparchive packages directory | gzip > Packages.gz

SEE ALSO
       apt.conf(5)

DIAGNOSTICS
       apt-ftparchive returns zero on normal operation, decimal 100 on error.

BUGS
       APT bug page[1]. If you wish to report a bug in APT, please see
       /usr/share/doc/debian/bug-reporting.txt or the reportbug(1) command.

AUTHORS
       Jason Gunthorpe

       APT team

NOTES
        1. APT bug page
           http://bugs.debian.org/src:apt

APT 2.6.1                                     29 January 2023                             APT-FTPARCHIVE(1)

## tldr apt-ftparchive
    NO INFORMATION

# apt-get

## man apt-get
APT-GET(8)                                          APT                                          APT-GET(8)

NAME
       apt-get - APT package handling utility -- command-line interface

SYNOPSIS
       apt-get [-asqdyfmubV] [-o=config_string] [-c=config_file] [-t=target_release] [-a=architecture]
               {update | upgrade | dselect-upgrade | dist-upgrade |
               install pkg [{=pkg_version_number | /target_release}]...  | remove pkg...  | purge pkg...  |
               source pkg [{=pkg_version_number | /target_release}]...  |
               build-dep pkg [{=pkg_version_number | /target_release}]...  |
               download pkg [{=pkg_version_number | /target_release}]...  | check | clean | autoclean |
               autoremove | {-v | --version} | {-h | --help}}

DESCRIPTION
       apt-get is the command-line tool for handling packages, and may be considered the user's "back-end"
       to other tools using the APT library. Several "front-end" interfaces exist, such as aptitude(8),
       synaptic(8) and wajig(1).

       Unless the -h, or --help option is given, one of the commands below must be present.

       update
           update is used to resynchronize the package index files from their sources. The indexes of
           available packages are fetched from the location(s) specified in /etc/apt/sources.list. For
           example, when using a Debian archive, this command retrieves and scans the Packages.gz files, so
           that information about new and updated packages is available. An update should always be
           performed before an upgrade or dist-upgrade. Please be aware that the overall progress meter
           will be incorrect as the size of the package files cannot be known in advance.

       upgrade
           upgrade is used to install the newest versions of all packages currently installed on the system
           from the sources enumerated in /etc/apt/sources.list. Packages currently installed with new
           versions available are retrieved and upgraded; under no circumstances are currently installed
           packages removed, or packages not already installed retrieved and installed. New versions of
           currently installed packages that cannot be upgraded without changing the install status of
           another package will be left at their current version. An update must be performed first so that
           apt-get knows that new versions of packages are available.

       dist-upgrade
           dist-upgrade in addition to performing the function of upgrade, also intelligently handles
           changing dependencies with new versions of packages; apt-get has a "smart" conflict resolution
           system, and it will attempt to upgrade the most important packages at the expense of less
           important ones if necessary. The dist-upgrade command may therefore remove some packages. The
           /etc/apt/sources.list file contains a list of locations from which to retrieve desired package
           files. See also apt_preferences(5) for a mechanism for overriding the general settings for
           individual packages.

       dselect-upgrade
           dselect-upgrade is used in conjunction with the traditional Debian packaging front-end,
           dselect(1).  dselect-upgrade follows the changes made by dselect(1) to the Status field of
           available packages, and performs the actions necessary to realize that state (for instance, the
           removal of old and the installation of new packages).

       install
           install is followed by one or more packages desired for installation or upgrading. Each package
           is a package name, not a fully qualified filename (for instance, in a Debian system, apt-utils
           would be the argument provided, not apt-utils_2.6.1_amd64.deb). All packages required by the
           package(s) specified for installation will also be retrieved and installed. The
           /etc/apt/sources.list file is used to locate the desired packages. If a hyphen is appended to
           the package name (with no intervening space), the identified package will be removed if it is
           installed. Similarly a plus sign can be used to designate a package to install. These latter
           features may be used to override decisions made by apt-get's conflict resolution system.

           A specific version of a package can be selected for installation by following the package name
           with an equals and the version of the package to select. This will cause that version to be
           located and selected for install. Alternatively a specific distribution can be selected by
           following the package name with a slash and the version of the distribution or the Archive name
           (stable, testing, unstable).

           Both of the version selection mechanisms can downgrade packages and must be used with care.

           This is also the target to use if you want to upgrade one or more already-installed packages
           without upgrading every package you have on your system. Unlike the "upgrade" target, which
           installs the newest version of all currently installed packages, "install" will install the
           newest version of only the package(s) specified. Simply provide the name of the package(s) you
           wish to upgrade, and if a newer version is available, it (and its dependencies, as described
           above) will be downloaded and installed.

           Finally, the apt_preferences(5) mechanism allows you to create an alternative installation
           policy for individual packages.

           If no package matches the given expression and the expression contains one of '.', '?' or '*'
           then it is assumed to be a POSIX regular expression, and it is applied to all package names in
           the database. Any matches are then installed (or removed). Note that matching is done by
           substring so 'lo.*' matches 'how-lo' and 'lowest'. If this is undesired, anchor the regular
           expression with a '^' or '$' character, or create a more specific regular expression.

           Fallback to regular expressions is deprecated in APT 2.0, has been removed in apt(8), except for
           anchored expressions, and will be removed from apt-get(8) in a future version. Use apt-
           patterns(5) instead.

       reinstall
           reinstall is an alias for install --reinstall.

       remove
           remove is identical to install except that packages are removed instead of installed. Note that
           removing a package leaves its configuration files on the system. If a plus sign is appended to
           the package name (with no intervening space), the identified package will be installed instead
           of removed.

       purge
           purge is identical to remove except that packages are removed and purged (any configuration
           files are deleted too).

       source
           source causes apt-get to fetch source packages. APT will examine the available packages to
           decide which source package to fetch. It will then find and download into the current directory
           the newest available version of that source package while respecting the default release, set
           with the option APT::Default-Release, the -t option or per package with the pkg/release syntax,
           if possible.

           The arguments are interpreted as binary and source package names. See the --only-source option
           if you want to change that.

           Source packages are tracked separately from binary packages via deb-src lines in the
           sources.list(5) file. This means that you will need to add such a line for each repository you
           want to get sources from; otherwise you will probably get either the wrong (too old/too new)
           source versions or none at all.

           If the --compile option is specified then the package will be compiled to a binary .deb using
           dpkg-buildpackage for the architecture as defined by the --host-architecture option. If
           --download-only is specified then the source package will not be unpacked.

           A specific source version can be retrieved by postfixing the source name with an equals and then
           the version to fetch, similar to the mechanism used for the package files. This enables exact
           matching of the source package name and version, implicitly enabling the APT::Get::Only-Source
           option.

           Note that source packages are not installed and tracked in the dpkg database like binary
           packages; they are simply downloaded to the current directory, like source tarballs.

       build-dep
           build-dep causes apt-get to install/remove packages in an attempt to satisfy the build
           dependencies for a source package. By default the dependencies are satisfied to build the
           package natively. If desired a host-architecture can be specified with the --host-architecture
           option instead.

           The arguments are interpreted as binary or source package names. See the --only-source option if
           you want to change that.

       satisfy
           satisfy causes apt-get to satisfy the given dependency strings. The dependency strings may have
           build profiles and architecture restriction list as in build dependencies. They may optionally
           be prefixed with "Conflicts: " to unsatisfy the dependency string. Multiple strings of the same
           type can be specified.

           Example: apt-get satisfy "foo" "Conflicts: bar" "baz (>> 1.0) | bar (= 2.0), moo"

           The legacy operator '</>' is not supported, use '<=/>=' instead.

       check
           check is a diagnostic tool; it updates the package cache and checks for broken dependencies.

       download
           download will download the given binary package into the current directory. The authenticity of
           the package data is ensured as usual.

       clean
           clean clears out the local repository of retrieved package files. It removes everything but the
           lock file from /var/cache/apt/archives/ and /var/cache/apt/archives/partial/.

       autoclean (and the auto-clean alias since 1.1)
           Like clean, autoclean clears out the local repository of retrieved package files. The difference
           is that it only removes package files that can no longer be downloaded, and are largely useless.
           This allows a cache to be maintained over a long period without it growing out of control. The
           configuration option APT::Clean-Installed will prevent installed packages from being erased if
           it is set to off.

       autoremove (and the auto-remove alias since 1.1)
           autoremove is used to remove packages that were automatically installed to satisfy dependencies
           for other packages and are now no longer needed.

       autopurge
           Like autoremove, but autopurge also removes configuration files. This is a shortcut for
           autoremove --purge.

       changelog
           changelog tries to download the changelog of a package and displays it through sensible-pager.
           By default it displays the changelog for the version that is installed. However, you can specify
           the same options as for the install command.

       indextargets
           Displays by default a deb822 formatted listing of information about all data files (aka index
           targets) apt-get update would download. Supports a --format option to modify the output format
           as well as accepts lines of the default output to filter the records by. The command is mainly
           used as an interface for external tools working with APT to get information as well as filenames
           for downloaded files so they can use them as well instead of downloading them again on their
           own. Detailed documentation is omitted here and can instead be found in the file
           /usr/share/doc/apt/acquire-additional-files.md.gz shipped by the apt-doc package.

OPTIONS
       All command line options may be set using the configuration file, the descriptions indicate the
       configuration option to set. For boolean options you can override the config file by using something
       like -f-,--no-f, -f=no or several other variations.

       --no-install-recommends
           Do not consider recommended packages as a dependency for installing. Configuration Item:
           APT::Install-Recommends.

       --install-suggests
           Consider suggested packages as a dependency for installing. Configuration Item:
           APT::Install-Suggests.

       -d, --download-only
           Download only; package files are only retrieved, not unpacked or installed. Configuration Item:
           APT::Get::Download-Only.

       -f, --fix-broken
           Fix; attempt to correct a system with broken dependencies in place. This option, when used with
           install/remove, can omit any packages to permit APT to deduce a likely solution. If packages are
           specified, these have to completely correct the problem. The option is sometimes necessary when
           running APT for the first time; APT itself does not allow broken package dependencies to exist
           on a system. It is possible that a system's dependency structure can be so corrupt as to require
           manual intervention (which usually means using dpkg --remove to eliminate some of the offending
           packages). Use of this option together with -m may produce an error in some situations.
           Configuration Item: APT::Get::Fix-Broken.

       -m, --ignore-missing, --fix-missing
           Ignore missing packages; if packages cannot be retrieved or fail the integrity check after
           retrieval (corrupted package files), hold back those packages and handle the result. Use of this
           option together with -f may produce an error in some situations. If a package is selected for
           installation (particularly if it is mentioned on the command line) and it could not be
           downloaded then it will be silently held back. Configuration Item: APT::Get::Fix-Missing.

       --no-download
           Disables downloading of packages. This is best used with --ignore-missing to force APT to use
           only the .debs it has already downloaded. Configuration Item: APT::Get::Download.

       -q, --quiet
           Quiet; produces output suitable for logging, omitting progress indicators. More q's will produce
           more quiet up to a maximum of 2. You can also use -q=# to set the quiet level, overriding the
           configuration file. Note that quiet level 2 implies -y; you should never use -qq without a
           no-action modifier such as -d, --print-uris or -s as APT may decide to do something you did not
           expect. Configuration Item: quiet.

       -s, --simulate, --just-print, --dry-run, --recon, --no-act
           No action; perform a simulation of events that would occur based on the current system state but
           do not actually change the system. Locking will be disabled (Debug::NoLocking) so the system
           state could change while apt-get is running. Simulations can also be executed by non-root users
           which might not have read access to all apt configuration distorting the simulation. A notice
           expressing this warning is also shown by default for non-root users
           (APT::Get::Show-User-Simulation-Note). Configuration Item: APT::Get::Simulate.

           Simulated runs print out a series of lines, each representing a dpkg operation: configure
           (Conf), remove (Remv) or unpack (Inst). Square brackets indicate broken packages, and empty
           square brackets indicate breaks that are of no consequence (rare).

       -y, --yes, --assume-yes
           Automatic yes to prompts; assume "yes" as answer to all prompts and run non-interactively. If an
           undesirable situation, such as changing a held package, trying to install an unauthenticated
           package or removing an essential package occurs then apt-get will abort. Configuration Item:
           APT::Get::Assume-Yes.

       --assume-no
           Automatic "no" to all prompts. Configuration Item: APT::Get::Assume-No.

       --no-show-upgraded
           Do not show a list of all packages that are to be upgraded. Configuration Item:
           APT::Get::Show-Upgraded.

       -V, --verbose-versions
           Show full versions for upgraded and installed packages. Configuration Item:
           APT::Get::Show-Versions.

       -a, --host-architecture
           This option controls the architecture packages are built for by apt-get source --compile and how
           cross-builddependencies are satisfied. By default is it not set which means that the host
           architecture is the same as the build architecture (which is defined by APT::Architecture).
           Configuration Item: APT::Get::Host-Architecture.

       -P, --build-profiles
           This option controls the activated build profiles for which a source package is built by apt-get
           source --compile and how build dependencies are satisfied. By default no build profile is
           active. More than one build profile can be activated at a time by concatenating them with a
           comma. Configuration Item: APT::Build-Profiles.

       -b, --compile, --build
           Compile source packages after downloading them. Configuration Item: APT::Get::Compile.

       --ignore-hold
           Ignore package holds; this causes apt-get to ignore a hold placed on a package. This may be
           useful in conjunction with dist-upgrade to override a large number of undesired holds.
           Configuration Item: APT::Ignore-Hold.

       --with-new-pkgs
           Allow installing new packages when used in conjunction with upgrade. This is useful if the
           update of an installed package requires new dependencies to be installed. Instead of holding the
           package back upgrade will upgrade the package and install the new dependencies. Note that
           upgrade with this option will never remove packages, only allow adding new ones. Configuration
           Item: APT::Get::Upgrade-Allow-New.

       --no-upgrade
           Do not upgrade packages; when used in conjunction with install, no-upgrade will prevent packages
           on the command line from being upgraded if they are already installed. Configuration Item:
           APT::Get::Upgrade.

       --only-upgrade
           Do not install new packages; when used in conjunction with install, only-upgrade will install
           upgrades for already installed packages only and ignore requests to install new packages.
           Configuration Item: APT::Get::Only-Upgrade.

       --allow-downgrades
           This is a dangerous option that will cause apt to continue without prompting if it is doing
           downgrades. It should not be used except in very special situations. Using it can potentially
           destroy your system! Configuration Item: APT::Get::allow-downgrades. Introduced in APT 1.1.

       --allow-remove-essential
           Force yes; this is a dangerous option that will cause apt to continue without prompting if it is
           removing essentials. It should not be used except in very special situations. Using it can
           potentially destroy your system! Configuration Item: APT::Get::allow-remove-essential.
           Introduced in APT 1.1.

       --allow-change-held-packages
           Force yes; this is a dangerous option that will cause apt to continue without prompting if it is
           changing held packages. It should not be used except in very special situations. Using it can
           potentially destroy your system! Configuration Item: APT::Get::allow-change-held-packages.
           Introduced in APT 1.1.

       --force-yes
           Force yes; this is a dangerous option that will cause apt to continue without prompting if it is
           doing something potentially harmful. It should not be used except in very special situations.
           Using force-yes can potentially destroy your system! Configuration Item: APT::Get::force-yes.
           This is deprecated and replaced by --allow-unauthenticated , --allow-downgrades ,
           --allow-remove-essential , --allow-change-held-packages in 1.1.

       --print-uris
           Instead of fetching the files to install their URIs are printed. Each URI will have the path,
           the destination file name, the size and the expected MD5 hash. Note that the file name to write
           to will not always match the file name on the remote site! This also works with the source and
           update commands. When used with the update command the MD5 and size are not included, and it is
           up to the user to decompress any compressed files. Configuration Item: APT::Get::Print-URIs.

       --purge
           Use purge instead of remove for anything that would be removed. An asterisk ("*") will be
           displayed next to packages which are scheduled to be purged.  remove --purge is equivalent to
           the purge command. Configuration Item: APT::Get::Purge.

       --reinstall
           Re-install packages that are already installed and at the newest version. Configuration Item:
           APT::Get::ReInstall.

       --list-cleanup
           This option is on by default; use --no-list-cleanup to turn it off. When it is on, apt-get will
           automatically manage the contents of /var/lib/apt/lists to ensure that obsolete files are
           erased. The only reason to turn it off is if you frequently change your sources list.
           Configuration Item: APT::Get::List-Cleanup.

       -t, --target-release, --default-release
           This option controls the default input to the policy engine; it creates a default pin at
           priority 990 using the specified release string. This overrides the general settings in
           /etc/apt/preferences. Specifically pinned packages are not affected by the value of this option.
           In short, this option lets you have simple control over which distribution packages will be
           retrieved from. Some common examples might be -t '2.1*', -t unstable or -t sid. Configuration
           Item: APT::Default-Release; see also the apt_preferences(5) manual page.

       --trivial-only
           Only perform operations that are 'trivial'. Logically this can be considered related to
           --assume-yes; where --assume-yes will answer yes to any prompt, --trivial-only will answer no.
           Configuration Item: APT::Get::Trivial-Only.

       --mark-auto
           After successful installation, mark all freshly installed packages as automatically installed,
           which will cause each of the packages to be removed when no more manually installed packages
           depend on this package. This is equally to running apt-mark auto for all installed packages.
           Configuration Item: APT::Get::Mark-Auto.

       --no-remove
           If any packages are to be removed apt-get immediately aborts without prompting. Configuration
           Item: APT::Get::Remove.

       --auto-remove, --autoremove
           If the command is either install or remove, then this option acts like running the autoremove
           command, removing unused dependency packages. Configuration Item: APT::Get::AutomaticRemove.

       --only-source
           Only has meaning for the source and build-dep commands. Indicates that the given source names
           are not to be mapped through the binary table. This means that if this option is specified,
           these commands will only accept source package names as arguments, rather than accepting binary
           package names and looking up the corresponding source package. Configuration Item:
           APT::Get::Only-Source.

       --diff-only, --dsc-only, --tar-only
           Download only the diff, dsc, or tar file of a source archive. Configuration Item:
           APT::Get::Diff-Only, APT::Get::Dsc-Only, and APT::Get::Tar-Only.

       --arch-only
           Only process architecture-dependent build-dependencies. Configuration Item: APT::Get::Arch-Only.

       --indep-only
           Only process architecture-independent build-dependencies. Configuration Item:
           APT::Get::Indep-Only.

       --allow-unauthenticated
           Ignore if packages can't be authenticated and don't prompt about it. This can be useful while
           working with local repositories, but is a huge security risk if data authenticity isn't ensured
           in another way by the user itself. The usage of the Trusted option for sources.list(5) entries
           should usually be preferred over this global override. Configuration Item:
           APT::Get::AllowUnauthenticated.

       --allow-insecure-repositories
           Allow the update command to acquire unverifiable data from configured sources. APT will
           otherwise fail at the update command for repositories without valid cryptographically
           signatures. See also apt-secure(8) for details on the concept and the implications.
           Configuration Item: Acquire::AllowInsecureRepositories.

       --allow-releaseinfo-change
           Allow the update command to continue downloading data from a repository which changed its
           information of the release contained in the repository indicating e.g a new major release. APT
           will fail at the update command for such repositories until the change is confirmed to ensure
           the user is prepared for the change. See also apt-secure(8) for details on the concept and
           configuration.

           Specialist options (--allow-releaseinfo-change-field) exist to allow changes only for certain
           fields like origin, label, codename, suite, version and defaultpin. See also apt_preferences(5).
           Configuration Item: Acquire::AllowReleaseInfoChange.

       --show-progress
           Show user friendly progress information in the terminal window when packages are installed,
           upgraded or removed. For a machine parsable version of this data see README.progress-reporting
           in the apt doc directory. Configuration Items: Dpkg::Progress and Dpkg::Progress-Fancy.

       --with-source filename
           Adds the given file as a source for metadata. Can be repeated to add multiple files. See
           --with-source description in apt-cache(8) for further details.

       -eany, --error-on=any
           Fail the update command if any error occured, even a transient one.

       -h, --help
           Show a short usage summary.

       -v, --version
           Show the program version.

       -c, --config-file
           Configuration File; Specify a configuration file to use. The program will read the default
           configuration file and then this configuration file. If configuration settings need to be set
           before the default configuration files are parsed specify a file with the APT_CONFIG environment
           variable. See apt.conf(5) for syntax information.

       -o, --option
           Set a Configuration Option; This will set an arbitrary configuration option. The syntax is -o
           Foo::Bar=bar.  -o and --option can be used multiple times to set different options.

FILES
       /etc/apt/sources.list
           Locations to fetch packages from. Configuration Item: Dir::Etc::SourceList.

       /etc/apt/sources.list.d/
           File fragments for locations to fetch packages from. Configuration Item: Dir::Etc::SourceParts.

       /etc/apt/apt.conf
           APT configuration file. Configuration Item: Dir::Etc::Main.

       /etc/apt/apt.conf.d/
           APT configuration file fragments. Configuration Item: Dir::Etc::Parts.

       /etc/apt/preferences
           Version preferences file. This is where you would specify "pinning", i.e. a preference to get
           certain packages from a separate source or from a different version of a distribution.
           Configuration Item: Dir::Etc::Preferences.

       /etc/apt/preferences.d/
           File fragments for the version preferences. Configuration Item: Dir::Etc::PreferencesParts.

       /var/cache/apt/archives/
           Storage area for retrieved package files. Configuration Item: Dir::Cache::Archives.

       /var/cache/apt/archives/partial/
           Storage area for package files in transit. Configuration Item: Dir::Cache::Archives (partial
           will be implicitly appended)

       /var/lib/apt/lists/
           Storage area for state information for each package resource specified in sources.list(5)
           Configuration Item: Dir::State::Lists.

       /var/lib/apt/lists/partial/
           Storage area for state information in transit. Configuration Item: Dir::State::Lists (partial
           will be implicitly appended)

SEE ALSO
       apt-cache(8), apt-cdrom(8), dpkg(1), sources.list(5), apt.conf(5), apt-config(8), apt-secure(8), The
       APT User's guide in /usr/share/doc/apt-doc/, apt_preferences(5), the APT Howto.

DIAGNOSTICS
       apt-get returns zero on normal operation, decimal 100 on error.

BUGS
       APT bug page[1]. If you wish to report a bug in APT, please see
       /usr/share/doc/debian/bug-reporting.txt or the reportbug(1) command.

AUTHORS
       Jason Gunthorpe

       APT team

NOTES
        1. APT bug page
           http://bugs.debian.org/src:apt

APT 2.6.1                                     25 January 2023                                    APT-GET(8)

## tldr apt-get
apt-get

[0m[0mDebian and Ubuntu package management utility.
Search for packages using apt-cache.
It is recommended to use apt when used interactively in Ubuntu versions 16.04 and later.
More information: https://manned.org/apt-get.8.

 - [0m[32;23;22;24;25mUpdate the list of available packages and versions (it's recommended to run this before other apt-get commands):
   [33;23;22;24;25msudo apt-get update[0m
[0m
 - [0m[32;23;22;24;25mInstall a package, or update it to the latest available version:
   [33;23;22;24;25msudo apt-get install [0mpackage
[0m
 - [0m[32;23;22;24;25mRemove a package:
   [33;23;22;24;25msudo apt-get remove [0mpackage
[0m
 - [0m[32;23;22;24;25mRemove a package and its configuration files:
   [33;23;22;24;25msudo apt-get purge [0mpackage
[0m
 - [0m[32;23;22;24;25mUpgrade all installed packages to their newest available versions:
   [33;23;22;24;25msudo apt-get upgrade[0m
[0m
 - [0m[32;23;22;24;25mClean the local repository - removing package files (.deb) from interrupted downloads that can no longer be downloaded:
   [33;23;22;24;25msudo apt-get autoclean[0m
[0m
 - [0m[32;23;22;24;25mRemove all packages that are no longer needed:
   [33;23;22;24;25msudo apt-get autoremove[0m
[0m
 - [0m[32;23;22;24;25mUpgrade installed packages (like upgrade), but remove obsolete packages and install additional packages to meet new dependencies:
   [33;23;22;24;25msudo apt-get dist-upgrade[0m
[0m[0m

# apt-key

## man apt-key
APT-KEY(8)                                          APT                                          APT-KEY(8)

NAME
       apt-key - Deprecated APT key management utility

SYNOPSIS
       apt-key [--keyring filename] {add filename | del keyid | export keyid | exportall | list | finger |
               adv | update | net-update | {-v | --version} | {-h | --help}}

DESCRIPTION
       apt-key is used to manage the list of keys used by apt to authenticate packages. Packages which have
       been authenticated using these keys will be considered trusted.

       Use of apt-key is deprecated, except for the use of apt-key del in maintainer scripts to remove
       existing keys from the main keyring. If such usage of apt-key is desired the additional installation
       of the GNU Privacy Guard suite (packaged in gnupg) is required.

       apt-key(8) will last be available in Debian 11 and Ubuntu 22.04.

SUPPORTED KEYRING FILES
       apt-key supports only the binary OpenPGP format (also known as "GPG key public ring") in files with
       the "gpg" extension, not the keybox database format introduced in newer gpg(1) versions as default
       for keyring files. Binary keyring files intended to be used with any apt version should therefore
       always be created with gpg --export.

       Alternatively, if all systems which should be using the created keyring have at least apt version >=
       1.4 installed, you can use the ASCII armored format with the "asc" extension instead which can be
       created with gpg --armor --export.

COMMANDS
       add filename (deprecated)
           Add a new key to the list of trusted keys. The key is read from the filename given with the
           parameter filename or if the filename is - from standard input.

           It is critical that keys added manually via apt-key are verified to belong to the owner of the
           repositories they claim to be for otherwise the apt-secure(8) infrastructure is completely
           undermined.

           Note: Instead of using this command a keyring should be placed directly in the
           /etc/apt/trusted.gpg.d/ directory with a descriptive name and either "gpg" or "asc" as file
           extension.

       del keyid (mostly deprecated)
           Remove a key from the list of trusted keys.

       export keyid (deprecated)
           Output the key keyid to standard output.

       exportall (deprecated)
           Output all trusted keys to standard output.

       list, finger (deprecated)
           List trusted keys with fingerprints.

       adv (deprecated)
           Pass advanced options to gpg. With adv --recv-key you can e.g. download key from keyservers
           directly into the trusted set of keys. Note that there are no checks performed, so it is easy to
           completely undermine the apt-secure(8) infrastructure if used without care.

       update (deprecated)
           Update the local keyring with the archive keyring and remove from the local keyring the archive
           keys which are no longer valid. The archive keyring is shipped in the archive-keyring package of
           your distribution, e.g. the debian-archive-keyring package in Debian.

           Note that a distribution does not need to and in fact should not use this command any longer and
           instead ship keyring files in the /etc/apt/trusted.gpg.d/ directory directly as this avoids a
           dependency on gnupg and it is easier to manage keys by simply adding and removing files for
           maintainers and users alike.

       net-update (deprecated)
           Perform an update working similarly to the update command above, but get the archive keyring
           from a URI instead and validate it against a master key. This requires an installed wget(1) and
           an APT build configured to have a server to fetch from and a master keyring to validate. APT in
           Debian does not support this command, relying on update instead, but Ubuntu's APT does.

OPTIONS
       Note that options need to be defined before the commands described in the previous section.

       --keyring filename (deprecated)
           With this option it is possible to specify a particular keyring file the command should operate
           on. The default is that a command is executed on the trusted.gpg file as well as on all parts in
           the trusted.gpg.d directory, though trusted.gpg is the primary keyring which means that e.g. new
           keys are added to this one.

DEPRECATION
       Except for using apt-key del in maintainer scripts, the use of apt-key is deprecated. This section
       shows how to replace existing use of apt-key.

       If your existing use of apt-key add looks like this:

       wget -qO- https://myrepo.example/myrepo.asc | sudo apt-key add -

       Then you can directly replace this with (though note the recommendation below):

       wget -qO- https://myrepo.example/myrepo.asc | sudo tee /etc/apt/trusted.gpg.d/myrepo.asc

       Make sure to use the "asc" extension for ASCII armored keys and the "gpg" extension for the binary
       OpenPGP format (also known as "GPG key public ring"). The binary OpenPGP format works for all apt
       versions, while the ASCII armored format works for apt version >= 1.4.

       Recommended: Instead of placing keys into the /etc/apt/trusted.gpg.d directory, you can place them
       anywhere on your filesystem by using the Signed-By option in your sources.list and pointing to the
       filename of the key. See sources.list(5) for details. Since APT 2.4, /etc/apt/keyrings is provided
       as the recommended location for keys not managed by packages. When using a deb822-style
       sources.list, and with apt version >= 2.4, the Signed-By option can also be used to include the full
       ASCII armored keyring directly in the sources.list without an additional file.

FILES
       /etc/apt/trusted.gpg
           Keyring of local trusted keys, new keys will be added here. Configuration Item:
           Dir::Etc::Trusted.

       /etc/apt/trusted.gpg.d/
           File fragments for the trusted keys, additional keyrings can be stored here (by other packages
           or the administrator). Configuration Item Dir::Etc::TrustedParts.

       /etc/apt/keyrings/
           Place to store additional keyrings to be used with Signed-By.

SEE ALSO
       apt-get(8), apt-secure(8)

BUGS
       APT bug page[1]. If you wish to report a bug in APT, please see
       /usr/share/doc/debian/bug-reporting.txt or the reportbug(1) command.

AUTHOR
       APT was written by the APT team <apt@packages.debian.org>.

AUTHORS
       Jason Gunthorpe

       APT team

NOTES
        1. APT bug page
           http://bugs.debian.org/src:apt

APT 2.6.1                                     22 February 2022                                   APT-KEY(8)

## tldr apt-key
apt-key

[0m[0mKey management utility for the APT Package Manager on Debian and Ubuntu.
Note: apt-key is now deprecated (except for the use of apt-key del in maintainer scripts).
More information: https://manned.org/apt-key.

 - [0m[32;23;22;24;25mList trusted keys:
   [33;23;22;24;25mapt-key list[0m
[0m
 - [0m[32;23;22;24;25mAdd a key to the trusted keystore:
   [33;23;22;24;25mapt-key add [0mpublic_key_file.asc
[0m
 - [0m[32;23;22;24;25mDelete a key from the trusted keystore:
   [33;23;22;24;25mapt-key del [0mkey_id
[0m
 - [0m[32;23;22;24;25mAdd a remote key to the trusted keystore:
   [33;23;22;24;25mwget [0m[-qO|--quiet --output-document][33;23;22;24;25m - [0mhttps://host.tld/filename.key[33;23;22;24;25m | apt-key add -[0m
[0m
 - [0m[32;23;22;24;25mAdd a key from keyserver with only key ID:
   [33;23;22;24;25mapt-key adv --keyserver [0mpgp.mit.edu[33;23;22;24;25m --recv [0mKEYID
[0m[0m

# apt-listchanges

## man apt-listchanges
APT-LISTCHANGES(1)                                 Debian                                APT-LISTCHANGES(1)

NAME
       apt-listchanges - Show new changelog entries from Debian package archives

SYNOPSIS
       apt-listchanges [[options...]] {[--apt] | [package.deb...]}

DESCRIPTION
       apt-listchanges is a tool to show what has been changed in a new version of a Debian package, as
       compared to the version currently installed on the system.

       It does this by extracting the relevant entries from both the NEWS.Debian and changelog[.Debian]
       files, usually found in /usr/share/doc/package, from Debian package archives.

       Please note that in the default installation if apt-listchanges is run during upgrades as an APT
       plugin, it displays NEWS.Debian entries only. This can be changed with the --which option.

       If changelog entries are displayed and the package does not contain changelog[.Debian] file,
       apt-listchanges calls apt-get changelog command to download the changelog from network. This
       behavior can be disabled with the --no-network option.

       Given a set of filenames as arguments (or read from apt when using --apt), apt-listchanges will scan
       the files (assumed to be Debian package archives) for the relevant changelog entries, and display
       them all in a summary grouped by source package. The groups are sorted by the urgency of the most
       urgent change, and than by the package name. Changes within each package group are displayed in the
       order of their appearance in the changelog files, i.e. starting from the latest to the oldest; the
       --reverse option can be used to alter this order.

OPTIONS
       apt-listchanges provides the following options to control its behavior. Most of them have their
       equivalent entries in the configuration file, see the "CONFIGURATION FILE" below for details.

       --apt
           Read filenames from a specially-formatted pipeline (as provided by apt), rather than from
           command line arguments, and honor certain apt-specific options in the config file. This pipeline
           must be in "version 2" format, specified in the apt configuration.

       -v, --verbose
           Display additional (usually unwanted) information. For instance, print a message when a package
           of the same or older version is to be installed, or when a package is to be newly installed.

       -f, --frontend
           Select which frontend to use to display information to the user. Current frontends include:

           pager
               Uses sensible-pager(1) command to display output. The command uses PAGER environment
               variable to choose your favourite pager. The "pager" option may be specified in the
               configuration file to select a specific pager for use with apt-listchanges.

           browser
               Displays an HTML-formatted changelog with hyperlinks for bugs and email addresses using the
               sensible-browser(1) command that examines BROWSER environment variable to choose your
               favourite browser. The "browser" option may be specified in the configuration file to select
               a specific browser for use with apt-listchanges.

           xterm-pager
               Uses your favorite pager to display output, but does so in an xterm (using the
               x-terminal-emulator alternative) in the background. This allows you to go on with the
               upgrade if you like, and continue to browse the changelogs. You can override the terminal
               emulator to be used with the "xterm" configuration option.

           xterm-browser
               The logical combination of xterm-pager and browser. Only appropriate for text-mode browsers.

           text
               Dumps output to stdout, with no pauses.

           syslog
               Dumps output to syslog. Disabling the titled option is recommended.

           log
               Appends output to a log file, with an optional filter process. Disabling the titled option
               is recommended.

           mail
               Sends mail to the address specified with --email-address, and does not display changelogs.

           gtk
               Spawns a gtk window to display the changelogs. Needs python3-gi to be installed.

           none
               Does nothing. Can be used to prevent apt-listchanges from running when configured to run
               automatically from apt.

           Please note that apt-listchanges will try to switch to an unprivileged user before spawning
           commands in "browser", "xterm-browser", and "xterm-pager" frontends. However this currently does
           not apply to the "pager" frontend. See also "ENVIRONMENT VARIABLES" below.

       --email-address=address
           In addition to displaying it, mail a copy of the changelog data to the specified address. To
           only mail changelog entries, use this option with the special frontend 'mail'.

       --email-format={text|html}
           If sending mail copies is enabled (see --email-address above), this option selects whether the
           mail should be sent as an old good plain text data (which is the default behavior), or as html
           data with clickable links, which might be more convenient for people using graphical mail
           clients.

       -c, --confirm
           Once changelogs have been displayed, ask the user whether or not to proceed. If the user chooses
           not to proceed, a nonzero exit status will be returned, and apt will abort.

       -a, --show-all
           Rather than trying to display changelog entries that are newer than the currently installed
           version of the package, simply display all changelog entries for all packages. This is useful
           for viewing the entire changelog of a .deb before extracting it.

       -n, --no-network
           In rare cases when a binary package (or to be more precise: none of the binary packages built
           from the same source package that are processed together as a group) does not contain a
           changelog file, apt-listchanges by default executes apt-get changelog to download changelogs
           from the network servers usually provided by your operating system distribution. This option
           will disable this behavior, what might be useful for example for systems behind a firewall.

       --save-seen=file
           This option will cause apt-listchanges to keep track of the last version of a package for which
           changelogs have been displayed, to avoid redisplaying the same changelogs in a future
           invocation. The database is stored in the named file. Specify 'none' to disable this feature.

       --dump-seen
           Display the contents of the seen database to standard output as a list of lines consisting of
           source package name and its latest seen version, separated by space. This option requires the
           path to the seen database to be known: please either specify it using --save-seen option or pass
           --profile=apt option to have it read from the configuration file.

       --since=version
           This option will cause apt-listchanges to show the entries later than the specified version.
           With this option, the only other argument you can pass is the path to a .deb file.

       --latest=N
           This option will cause apt-listchanges to show only the latest N entries. With this option, the
           only other argument you can pass is the path to a .deb file.

       --which={news|changelogs|both}
           This option selects whether news (from NEWS.Debian et al.), changelogs (from changelog.Debian et
           al.) or both should be displayed. The default is to display only news.

       --help
           Displays syntax information.

       -h, --headers
           These options will cause apt-listchanges to insert a header before each package's changelog
           showing the name of the package, and the names of the binary packages which are being upgraded
           (if there is more than one, or it differs from the source package name).

       --debug
           Display some debugging information.

       --profile=name
           Select an option profile.  name corresponds to a section in /etc/apt/listchanges.conf. The
           default when invoked from apt is "apt", and "cmdline" otherwise.

       --log=file
           Select the file appended to by the log frontend. The default is /var/log/apt/listchanges.log.
           The filter command option can be used to modify the output before it is appended to the log
           file. Please ensure that you setup log rotation for this file.

       --filter=command
           Select the command used to filter output before it is appended to the log file by the log
           frontend. stdin will receive the apt-listchanges output and stdout will be appended to the log
           file. Separate arguments with spaces and quote arguments containing spaces. The command will not
           be run using the shell unless the shell is included in the command: sh -c 'date ; cat'

       --reverse
           Show the changelog entries in reverse order.

       --ignore-apt-assume, --ignore-debian-frontend
           Disable forcing non-interactive frontend in some of the cases described in the "AUTOMATIC
           FRONTEND OVERRIDE" section below.

       --titled, --untitled
           Enable or disable the title at the beginning of the output.

       --select-frontend
           Choose frontend interactively. This option is mainly for testing purposes, please do not use it.

AUTOMATIC FRONTEND OVERRIDE
       For a better integration with existing package management tools, apt-listchanges tries to detect if
       package upgrades are done in a non-interactive way, and automatically switches its frontend to
       'text' when any of the following conditions is satisfied:

       •   the standard output is not connected to terminal;

       •   the --quiet (-q) option is given to apt-get(8) (or aptitude(8)); note however that when the
           option is used more than once, apt-listchanges switches the frontend to 'mail';

       •   the --assume-yes (-y) option is given to apt-get(8);

       •   the DEBIAN_FRONTEND environment variable is set to "noninteractive", and APT_LISTCHANGES_FRONTED
           is not set.

       For backward compatibility purposes the last two of the above checks can be disabled either with
       "ignore_apt_assume=true" or "ignore_debian_frontend=true" configuration file entries (see
       "CONFIGURATION FILE" below) or by using the command line options: --ignore-apt-assume or
       --ignore-debian-frontend.

       Please also note that the "mail" frontend is already non-interactive one, so it is never switched to
       the "text" frontend.

       Additionally apt-listchanges overrides X11-based frontends ("gtk", "xterm-pager", "xterm-browser")
       with "pager" (or "browser" in case of "xterm-browser") when the environment variable DISPLAY is not
       set.

       Please note that these silent frontends are not subject to the overrides: syslog log

CONFIGURATION FILE
       apt-listchanges reads its configuration from the /etc/apt/listchanges.conf. The file consists of
       sections with names enclosed in the square brackets. Each section should contain lines in the
       key=value format. Lines starting with the "#" sign are treated as comments and ignored. Files named
       name.conf in the /etc/apt/listchanges.conf.d directory are also read in the same way and override
       values set in the main configuration file.

       Section is a name of profile that can be used as parameter of the --profile option.

       The configuration of the "apt" section can be managed by debconf(7), and most of the settings there
       can be changed with the help of the dpkg-reconfigure apt-listchanges command.

       Key is a name of some command-line option (except for --apt, --profile, --help) with the initial
       hyphens removed, and the remaining hyphens translated to underscores, for example: "email_format" or
       "save_seen".

       Value represents the value of the corresponding option. For command-line options that do not take
       argument, like "confirm" or "headers", the value should be set either to "1", "yes", "true", and
       "on" in order to enable the option, or to "0", "no", "false", and "off" to disable it.

       Additionally key can be one of the following keywords: "browser", "pager" or "xterm". The value of
       such configuration entry should be the name of an appropriate command, eventually followed by its
       arguments, for example: "pager=less -R".

       Example 1. Example configuration file

           [cmdline]
           frontend=pager

           [apt]
           frontend=xterm-pager
           email_address=root
           confirm=1

           [custom]
           frontend=browser
           browser=mozilla

       The above configuration file specifies that in command-line mode, the default frontend should be
       "pager". In apt mode, the xterm-pager frontend is default, a copy of the changelogs (if any) should
       be emailed to root, and apt-listchanges should ask for confirmation. If apt-listchanges is invoked
       with --profile=custom, the browser frontend will be used, and invoke mozilla.

ENVIRONMENT
       APT_LISTCHANGES_FRONTEND
           Frontend to use.

       APT_LISTCHANGES_USER, SUDO_USER, USERNAME
           The value of the first existing of the above variables will be used as the name of user to
           switch to when running commands spawned by the "browser", "xterm-browser", and "xterm-pager"
           frontends if apt-listchanges is started by a privileged user.

       DEBIAN_FRONTEND
           If set to "noninteractive", then it can force apt-listchanges to use non-interactive frontend,
           see the "AUTOMATIC FRONTEND OVERRIDE" section for details.

       BROWSER
           Used by the browser frontend, should be set to a command expecting a file: URL for an HTML file
           to display.

       PAGER
           Used by the pager frontend.

       APT_HOOK_INFO_FD
           File descriptor to read package names from in the --apt mode. (Apt is expected to set this
           variable to a proper file descriptor number).

FILES
       /etc/apt/listchanges.conf
           Configuration file.

       /etc/apt/listchanges.conf.d/*.conf
           Configuration file override files.

       /etc/apt/apt.conf.d/20listchanges
           File used for registering apt-listchanges into apt system.

       /var/lib/apt/listchanges.db
           Database used for save-seen.

AUTHOR
       apt-listchanges was written by Matt Zimmerman <mdz@debian.org>

       The current maintainer is Robert Luberda <robert@debian.org>

SEE ALSO
       sensible-pager(1), sensible-browser(1), apt-get(8), aptitude(8)

apt-listchanges                                  2017-07-08                              APT-LISTCHANGES(1)

## tldr apt-listchanges
NO INFORMATION

# apt-mark
# man apt-mark
APT-MARK(8)                                         APT                                         APT-MARK(8)

NAME
       apt-mark - show, set and unset various settings for a package

SYNOPSIS
       apt-mark {-f=filename | {auto | manual} pkg...  | {showauto | showmanual} [pkg...] } |
                {-v | --version} | {-h | --help}

       apt-mark {hold | unhold | install | remove | purge} pkg...  |
                {showhold | showinstall | showremove | showpurge} [pkg...]

DESCRIPTION
       apt-mark can be used as a unified front-end to set various settings for a package, such as marking a
       package as being automatically/manually installed or changing dpkg selections such as hold, install,
       deinstall and purge which are respected e.g. by apt-get dselect-upgrade or aptitude.

AUTOMATICALLY AND MANUALLY INSTALLED PACKAGES
       When you request that a package is installed, and as a result other packages are installed to
       satisfy its dependencies, the dependencies are marked as being automatically installed, while the
       package you installed explicitly is marked as manually installed. Once an automatically installed
       package is no longer depended on by any manually installed package it is considered no longer needed
       and e.g.  apt-get or aptitude will at least suggest removing them.

       auto
           auto is used to mark a package as being automatically installed, which will cause the package to
           be removed when no more manually installed packages depend on this package.

       manual
           manual is used to mark a package as being manually installed, which will prevent the package
           from being automatically removed if no other packages depend on it.

       minimize-manual
           minimize-manual is used to mark (transitive) dependencies of metapackages as automatically
           installed. This can be used after an installation for example, to minimize the number of
           manually installed packages; or continuously on systems managed by system configuration
           metapackages.

       showauto
           showauto is used to print a list of automatically installed packages with each package on a new
           line. All automatically installed packages will be listed if no package is given. If packages
           are given only those which are automatically installed will be shown.

       showmanual
           showmanual can be used in the same way as showauto except that it will print a list of manually
           installed packages instead.

   Options
       -f=filename, --file=filename
           Read/Write package stats from the filename given with the parameter filename instead of from the
           default location, which is extended_states in the directory defined by the Configuration Item:
           Dir::State.

PREVENT CHANGES FOR A PACKAGE
       hold
           hold is used to mark a package as held back, which will prevent the package from being
           automatically installed, upgraded or removed.

       unhold
           unhold is used to cancel a previously set hold on a package to allow all actions again.

       showhold
           showhold is used to print a list of packages on hold in the same way as for the other show
           commands.

SCHEDULE PACKAGES FOR INSTALL, REMOVE AND PURGE
       Some front-ends like apt-get dselect-upgrade can be used to apply previously scheduled changes to
       the install state of packages. Such changes can be scheduled with the install, remove (also known as
       deinstall) and purge commands. Packages with a specific selection can be displayed with showinstall,
       showremove and showpurge respectively. More information about these so called dpkg selections can be
       found in dpkg(1).

OPTIONS
       -h, --help
           Show a short usage summary.

       -v, --version
           Show the program version.

       -c, --config-file
           Configuration File; Specify a configuration file to use. The program will read the default
           configuration file and then this configuration file. If configuration settings need to be set
           before the default configuration files are parsed specify a file with the APT_CONFIG environment
           variable. See apt.conf(5) for syntax information.

       -o, --option
           Set a Configuration Option; This will set an arbitrary configuration option. The syntax is -o
           Foo::Bar=bar.  -o and --option can be used multiple times to set different options.

FILES
       /var/lib/apt/extended_states
           Status list of auto-installed packages. Configuration Item: Dir::State::extended_states.

SEE ALSO
       apt-get(8),aptitude(8),apt.conf(5)

DIAGNOSTICS
       apt-mark returns zero on normal operation, non-zero on error.

BUGS
       APT bug page[1]. If you wish to report a bug in APT, please see
       /usr/share/doc/debian/bug-reporting.txt or the reportbug(1) command.

AUTHORS
       Mike O'Connor

       APT team

NOTES
        1. APT bug page
           http://bugs.debian.org/src:apt

APT 2.6.1                                     11 December 2018                                  APT-MARK(8)

## tldr apt-mark
apt-mark

[0m[0mUtility to change the status of installed packages.
More information: https://manned.org/apt-mark.

 - [0m[32;23;22;24;25mMark a package as automatically installed:
   [33;23;22;24;25msudo apt-mark auto [0mpackage
[0m
 - [0m[32;23;22;24;25mHold a package at its current version and prevent updates to it:
   [33;23;22;24;25msudo apt-mark hold [0mpackage
[0m
 - [0m[32;23;22;24;25mAllow a package to be updated again:
   [33;23;22;24;25msudo apt-mark unhold [0mpackage
[0m
 - [0m[32;23;22;24;25mShow manually installed packages:
   [33;23;22;24;25mapt-mark showmanual[0m
[0m
 - [0m[32;23;22;24;25mShow held packages that aren't being updated:
   [33;23;22;24;25mapt-mark showhold[0m
[0m[0m

# apt-sortpkgs

## man apt-sortpkgs
APT-SORTPKGS(1)                                     APT                                     APT-SORTPKGS(1)

NAME
       apt-sortpkgs - Utility to sort package index files

SYNOPSIS
       apt-sortpkgs [-s] [-o=config_string] [-c=config_file] filename... {-v | --version} {-h | --help}

DESCRIPTION
       apt-sortpkgs will take an index file (source index or package index) and sort the records so that
       they are ordered by the package name. It will also sort the internal fields of each record according
       to the internal sorting rules.

       All output is sent to standard output; the input must be a seekable file.

OPTIONS
       All command line options may be set using the configuration file, the descriptions indicate the
       configuration option to set. For boolean options you can override the config file by using something
       like -f-,--no-f, -f=no or several other variations.

       -s, --source
           Use source index field ordering. Configuration Item: APT::SortPkgs::Source.

       -h, --help
           Show a short usage summary.

       -v, --version
           Show the program version.

       -c, --config-file
           Configuration File; Specify a configuration file to use. The program will read the default
           configuration file and then this configuration file. If configuration settings need to be set
           before the default configuration files are parsed specify a file with the APT_CONFIG environment
           variable. See apt.conf(5) for syntax information.

       -o, --option
           Set a Configuration Option; This will set an arbitrary configuration option. The syntax is -o
           Foo::Bar=bar.  -o and --option can be used multiple times to set different options.

SEE ALSO
       apt.conf(5)

DIAGNOSTICS
       apt-sortpkgs returns zero on normal operation, decimal 100 on error.

BUGS
       APT bug page[1]. If you wish to report a bug in APT, please see
       /usr/share/doc/debian/bug-reporting.txt or the reportbug(1) command.

AUTHORS
       Jason Gunthorpe

       APT team

NOTES
        1. APT bug page
           http://bugs.debian.org/src:apt

APT 2.6.1                                     30 November 2013                              APT-SORTPKGS(1)

## tldr apt-sortpkgs
NO INFORMATION

# ar

## man ar
AR(1)                                      GNU Development Tools                                      AR(1)

NAME
       ar - create, modify, and extract from archives

SYNOPSIS
       ar [-X32_64] [-]p[mod] [--plugin name] [--target bfdname] [--output dirname] [--record-libdeps
       libdeps] [--thin] [relpos] [count] archive [member...]

DESCRIPTION
       The GNU ar program creates, modifies, and extracts from archives.  An archive is a single file
       holding a collection of other files in a structure that makes it possible to retrieve the original
       individual files (called members of the archive).

       The original files' contents, mode (permissions), timestamp, owner, and group are preserved in the
       archive, and can be restored on extraction.

       GNU ar can maintain archives whose members have names of any length; however, depending on how ar is
       configured on your system, a limit on member-name length may be imposed for compatibility with
       archive formats maintained with other tools.  If it exists, the limit is often 15 characters
       (typical of formats related to a.out) or 16 characters (typical of formats related to coff).

       ar is considered a binary utility because archives of this sort are most often used as libraries
       holding commonly needed subroutines.  Since libraries often will depend on other libraries, ar can
       also record the dependencies of a library when the --record-libdeps option is specified.

       ar creates an index to the symbols defined in relocatable object modules in the archive when you
       specify the modifier s.  Once created, this index is updated in the archive whenever ar makes a
       change to its contents (save for the q update operation).  An archive with such an index speeds up
       linking to the library, and allows routines in the library to call each other without regard to
       their placement in the archive.

       You may use nm -s or nm --print-armap to list this index table.  If an archive lacks the table,
       another form of ar called ranlib can be used to add just the table.

       GNU ar can optionally create a thin archive, which contains a symbol index and references to the
       original copies of the member files of the archive.  This is useful for building libraries for use
       within a local build tree, where the relocatable objects are expected to remain available, and
       copying the contents of each object would only waste time and space.

       An archive can either be thin or it can be normal.  It cannot be both at the same time.  Once an
       archive is created its format cannot be changed without first deleting it and then creating a new
       archive in its place.

       Thin archives are also flattened, so that adding one thin archive to another thin archive does not
       nest it, as would happen with a normal archive.  Instead the elements of the first archive are added
       individually to the second archive.

       The paths to the elements of the archive are stored relative to the archive itself.

       GNU ar is designed to be compatible with two different facilities.  You can control its activity
       using command-line options, like the different varieties of ar on Unix systems; or, if you specify
       the single command-line option -M, you can control it with a script supplied via standard input,
       like the MRI "librarian" program.

OPTIONS
       GNU ar allows you to mix the operation code p and modifier flags mod in any order, within the first
       command-line argument.

       If you wish, you may begin the first command-line argument with a dash.

       The p keyletter specifies what operation to execute; it may be any of the following, but you must
       specify only one of them:

       d   Delete modules from the archive.  Specify the names of modules to be deleted as member...; the
           archive is untouched if you specify no files to delete.

           If you specify the v modifier, ar lists each module as it is deleted.

       m   Use this operation to move members in an archive.

           The ordering of members in an archive can make a difference in how programs are linked using the
           library, if a symbol is defined in more than one member.

           If no modifiers are used with "m", any members you name in the member arguments are moved to the
           end of the archive; you can use the a, b, or i modifiers to move them to a specified place
           instead.

       p   Print the specified members of the archive, to the standard output file.  If the v modifier is
           specified, show the member name before copying its contents to standard output.

           If you specify no member arguments, all the files in the archive are printed.

       q   Quick append; Historically, add the files member... to the end of archive, without checking for
           replacement.

           The modifiers a, b, and i do not affect this operation; new members are always placed at the end
           of the archive.

           The modifier v makes ar list each file as it is appended.

           Since the point of this operation is speed, implementations of ar have the option of not
           updating the archive's symbol table if one exists.  Too many different systems however assume
           that symbol tables are always up-to-date, so GNU ar will rebuild the table even with a quick
           append.

           Note - GNU ar treats the command qs as a synonym for r - replacing already existing files in the
           archive and appending new ones at the end.

       r   Insert the files member... into archive (with replacement). This operation differs from q in
           that any previously existing members are deleted if their names match those being added.

           If one of the files named in member... does not exist, ar displays an error message, and leaves
           undisturbed any existing members of the archive matching that name.

           By default, new members are added at the end of the file; but you may use one of the modifiers
           a, b, or i to request placement relative to some existing member.

           The modifier v used with this operation elicits a line of output for each file inserted, along
           with one of the letters a or r to indicate whether the file was appended (no old member deleted)
           or replaced.

       s   Add an index to the archive, or update it if it already exists.  Note this command is an
           exception to the rule that there can only be one command letter, as it is possible to use it as
           either a command or a modifier.  In either case it does the same thing.

       t   Display a table listing the contents of archive, or those of the files listed in member... that
           are present in the archive.  Normally only the member name is shown, but if the modifier O is
           specified, then the corresponding offset of the member is also displayed.  Finally, in order to
           see the modes (permissions), timestamp, owner, group, and size the v modifier should be
           included.

           If you do not specify a member, all files in the archive are listed.

           If there is more than one file with the same name (say, fie) in an archive (say b.a), ar t b.a
           fie lists only the first instance; to see them all, you must ask for a complete listing---in our
           example, ar t b.a.

       x   Extract members (named member) from the archive.  You can use the v modifier with this
           operation, to request that ar list each name as it extracts it.

           If you do not specify a member, all files in the archive are extracted.

           Files cannot be extracted from a thin archive, and there are restrictions on extracting from
           archives created with P: The paths must not be absolute, may not contain "..", and any
           subdirectories in the paths must exist.  If it is desired to avoid these restrictions then used
           the --output option to specify an output directory.

       A number of modifiers (mod) may immediately follow the p keyletter, to specify variations on an
       operation's behavior:

       a   Add new files after an existing member of the archive.  If you use the modifier a, the name of
           an existing archive member must be present as the relpos argument, before the archive
           specification.

       b   Add new files before an existing member of the archive.  If you use the modifier b, the name of
           an existing archive member must be present as the relpos argument, before the archive
           specification.  (same as i).

       c   Create the archive.  The specified archive is always created if it did not exist, when you
           request an update.  But a warning is issued unless you specify in advance that you expect to
           create it, by using this modifier.

       D   Operate in deterministic mode.  When adding files and the archive index use zero for UIDs, GIDs,
           timestamps, and use consistent file modes for all files.  When this option is used, if ar is
           used with identical options and identical input files, multiple runs will create identical
           output files regardless of the input files' owners, groups, file modes, or modification times.

           If binutils was configured with --enable-deterministic-archives, then this mode is on by
           default.  It can be disabled with the U modifier, below.

       f   Truncate names in the archive.  GNU ar will normally permit file names of any length.  This will
           cause it to create archives which are not compatible with the native ar program on some systems.
           If this is a concern, the f modifier may be used to truncate file names when putting them in the
           archive.

       i   Insert new files before an existing member of the archive.  If you use the modifier i, the name
           of an existing archive member must be present as the relpos argument, before the archive
           specification.  (same as b).

       l   Specify dependencies of this library.  The dependencies must immediately follow this option
           character, must use the same syntax as the linker command line, and must be specified within a
           single argument.  I.e., if multiple items are needed, they must be quoted to form a single
           command line argument.  For example L "-L/usr/local/lib -lmydep1 -lmydep2"

       N   Uses the count parameter.  This is used if there are multiple entries in the archive with the
           same name.  Extract or delete instance count of the given name from the archive.

       o   Preserve the original dates of members when extracting them.  If you do not specify this
           modifier, files extracted from the archive are stamped with the time of extraction.

       O   Display member offsets inside the archive. Use together with the t option.

       P   Use the full path name when matching or storing names in the archive.  Archives created with
           full path names are not POSIX compliant, and thus may not work with tools other than up to date
           GNU tools.  Modifying such archives with GNU ar without using P will remove the full path names
           unless the archive is a thin archive.  Note that P may be useful when adding files to a thin
           archive since r without P ignores the path when choosing which element to replace.  Thus

                   ar rcST archive.a subdir/file1 subdir/file2 file1

           will result in the first "subdir/file1" being replaced with "file1" from the current directory.
           Adding P will prevent this replacement.

       s   Write an object-file index into the archive, or update an existing one, even if no other change
           is made to the archive.  You may use this modifier flag either with any operation, or alone.
           Running ar s on an archive is equivalent to running ranlib on it.

       S   Do not generate an archive symbol table.  This can speed up building a large library in several
           steps.  The resulting archive can not be used with the linker.  In order to build a symbol
           table, you must omit the S modifier on the last execution of ar, or you must run ranlib on the
           archive.

       T   Deprecated alias for --thin.  T is not recommended because in many ar implementations T has a
           different meaning, as specified by X/Open System Interface.

       u   Normally, ar r... inserts all files listed into the archive.  If you would like to insert only
           those of the files you list that are newer than existing members of the same names, use this
           modifier.  The u modifier is allowed only for the operation r (replace).  In particular, the
           combination qu is not allowed, since checking the timestamps would lose any speed advantage from
           the operation q.

       U   Do not operate in deterministic mode.  This is the inverse of the D modifier, above: added files
           and the archive index will get their actual UID, GID, timestamp, and file mode values.

           This is the default unless binutils was configured with --enable-deterministic-archives.

       v   This modifier requests the verbose version of an operation.  Many operations display additional
           information, such as filenames processed, when the modifier v is appended.

       V   This modifier shows the version number of ar.

       The ar program also supports some command-line options which are neither modifiers nor actions, but
       which do change its behaviour in specific ways:

       --help
           Displays the list of command-line options supported by ar and then exits.

       --version
           Displays the version information of ar and then exits.

       -X32_64
           ar ignores an initial option spelled -X32_64, for compatibility with AIX.  The behaviour
           produced by this option is the default for GNU ar.  ar does not support any of the other -X
           options; in particular, it does not support -X32 which is the default for AIX ar.

       --plugin name
           The optional command-line switch --plugin name causes ar to load the plugin called name which
           adds support for more file formats, including object files with link-time optimization
           information.

           This option is only available if the toolchain has been built with plugin support enabled.

           If --plugin is not provided, but plugin support has been enabled then ar iterates over the files
           in ${libdir}/bfd-plugins in alphabetic order and the first plugin that claims the object in
           question is used.

           Please note that this plugin search directory is not the one used by ld's -plugin option.  In
           order to make ar use the  linker plugin it must be copied into the ${libdir}/bfd-plugins
           directory.  For GCC based compilations the linker plugin is called liblto_plugin.so.0.0.0.  For
           Clang based compilations it is called LLVMgold.so.  The GCC plugin is always backwards
           compatible with earlier versions, so it is sufficient to just copy the newest one.

       --target target
           The optional command-line switch --target bfdname specifies that the archive members are in an
           object code format different from your system's default format.  See

       --output dirname
           The --output option can be used to specify a path to a directory into which archive members
           should be extracted.  If this option is not specified then the current directory will be used.

           Note - although the presence of this option does imply a x extraction operation that option must
           still be included on the command line.

       --record-libdeps libdeps
           The --record-libdeps option is identical to the l modifier, just handled in long form.

       --thin
           Make the specified archive a thin archive.  If it already exists and is a regular archive, the
           existing members must be present in the same directory as archive.

       @file
           Read command-line options from file.  The options read are inserted in place of the original
           @file option.  If file does not exist, or cannot be read, then the option will be treated
           literally, and not removed.

           Options in file are separated by whitespace.  A whitespace character may be included in an
           option by surrounding the entire option in either single or double quotes.  Any character
           (including a backslash) may be included by prefixing the character to be included with a
           backslash.  The file may itself contain additional @file options; any such options will be
           processed recursively.

SEE ALSO
       nm(1), ranlib(1), and the Info entries for binutils.

COPYRIGHT
       Copyright (c) 1991-2023 Free Software Foundation, Inc.

       Permission is granted to copy, distribute and/or modify this document under the terms of the GNU
       Free Documentation License, Version 1.3 or any later version published by the Free Software
       Foundation; with no Invariant Sections, with no Front-Cover Texts, and with no Back-Cover Texts.  A
       copy of the license is included in the section entitled "GNU Free Documentation License".

binutils-2.40.00                                 2023-01-14                                           AR(1)

## tldr arar

[0m[0mCreate, modify, and extract from Unix archives. Typically used for static libraries (.a) and Debian packages (.deb).
See also: tar.
More information: https://manned.org/ar.

 - [0m[32;23;22;24;25mE[x]tract all members from an archive:
   [33;23;22;24;25mar x [0mpath/to/file.a
[0m
 - [0m[32;23;22;24;25mLis[t] contents in a specific archive:
   [33;23;22;24;25mar t [0mpath/to/file.ar
[0m
 - [0m[32;23;22;24;25m[r]eplace or add specific files to an archive:
   [33;23;22;24;25mar r [0mpath/to/file.deb[33;23;22;24;25m [0mpath/to/debian-binary path/to/control.tar.gz path/to/data.tar.xz ...
[0m
 - [0m[32;23;22;24;25mIn[s]ert an object file index (equivalent to using ranlib):
   [33;23;22;24;25mar s [0mpath/to/file.a
[0m
 - [0m[32;23;22;24;25mCreate an archive with specific files and an accompanying object file index:
   [33;23;22;24;25mar rs [0mpath/to/file.a[33;23;22;24;25m [0mpath/to/file1.o path/to/file2.o ...
[0m[0m

# arborist

## man arborist
INDEX.JS(1)                                    User Commands                                    INDEX.JS(1)

NAME
       index.js - the npm tree doctor

DESCRIPTION
       Arborist - the npm tree doctor

       Version: 6.1.5

       Error: command 'undefined' does not exist.

       # USAGE

              arborist <cmd> [path] [options...]

       # COMMANDS

              *  reify:  reify  ideal  tree  to node_modules (install, update, rm, ...)  * prune: prune the
              ideal tree and reify (like npm prune) * ideal: generate and print the ideal  tree  *  actual:
              read  and print the actual tree in node_modules * virtual: read and print the virtual tree in
              the local shrinkwrap file * shrinkwrap: load a local shrinkwrap and print its data  *  audit:
              perform  a security audit on project dependencies * funding: query funding information in the
              local package tree.  A second

              positional argument after the path name can limit to a package name.

       * license: query license information in the local package tree.
              A second

              positional argument after the path name can limit to a license type.

              * help: print this text * version: print the version

       # OPTIONS

       Most npm options are supported, but in camelCase rather than css-case.
              For

              example, instead of '--dry-run', use '--dryRun'.

              Additionally:

              *  --loglevel=warn|--quiet  will  supppress  the  printing  of  package  trees  *   --logfile
              <file|bool>  will  output logs to a file * --timing will show timing information * Instead of
              'npm install <pkg>', use 'arborist reify --add=<pkg>'.

              The '--add=<pkg>' option can be specified multiple times.

              * Instead of 'npm rm <pkg>', use 'arborist reify --rm=<pkg>'.

              The '--rm=<pkg>' option can be specified multiple times.

              * Instead of 'npm update', use 'arborist reify --update-all'.  * 'npm audit fix' is 'arborist
              audit --fix'

index.js 6.1.5                                 December 2022                                    INDEX.JS(1)

## tldr arborist
NO INFORMATION

# arch

## man arch

ARCH(1)                                        User Commands                                        ARCH(1)

NAME
       arch - print machine hardware name (same as uname -m)

SYNOPSIS
       arch [OPTION]...

DESCRIPTION
       Print machine architecture.

       --help display this help and exit

       --version
              output version information and exit

AUTHOR
       Written by David MacKenzie and Karel Zak.

REPORTING BUGS
       GNU coreutils online help: <https://www.gnu.org/software/coreutils/>
       Report any translation bugs to <https://translationproject.org/team/>

COPYRIGHT
       Copyright  ©  2022  Free  Software  Foundation,  Inc.   License  GPLv3+:  GNU GPL version 3 or later
       <https://gnu.org/licenses/gpl.html>.
       This is free software: you are free to change and redistribute it.  There is NO WARRANTY, to the ex‐
       tent permitted by law.

SEE ALSO
       uname(1), uname(2)

       Full documentation <https://www.gnu.org/software/coreutils/arch>
       or available locally via: info '(coreutils) arch invocation'

GNU coreutils 9.1                              September 2022                                       ARCH(1)

## tldr arch
arch

[0m[0mThis command is an alias of uname --machine.

 - [0m[32;23;22;24;25mView documentation for the original command:
   [33;23;22;24;25mtldr uname[0m
[0m[0m

# 