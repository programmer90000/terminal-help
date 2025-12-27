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

# basename

## man basename
BASENAME(1)                                    User Commands                                    BASENAME(1)

NAME
       basename - strip directory and suffix from filenames

SYNOPSIS
       basename NAME [SUFFIX]
       basename OPTION... NAME...

DESCRIPTION
       Print NAME with any leading directory components removed.  If specified, also remove a trailing SUF‐
       FIX.

       Mandatory arguments to long options are mandatory for short options too.

       -a, --multiple
              support multiple arguments and treat each as a NAME

       -s, --suffix=SUFFIX
              remove a trailing SUFFIX; implies -a

       -z, --zero
              end each output line with NUL, not newline

       --help display this help and exit

       --version
              output version information and exit

EXAMPLES
       basename /usr/bin/sort
              -> "sort"

       basename include/stdio.h .h
              -> "stdio"

       basename -s .h include/stdio.h
              -> "stdio"

       basename -a any/str1 any/str2
              -> "str1" followed by "str2"

AUTHOR
       Written by David MacKenzie.

REPORTING BUGS
       GNU coreutils online help: <https://www.gnu.org/software/coreutils/>
       Report any translation bugs to <https://translationproject.org/team/>

COPYRIGHT
       Copyright © 2022 Free Software Foundation,  Inc.   License  GPLv3+:  GNU  GPL  version  3  or  later
       <https://gnu.org/licenses/gpl.html>.
       This is free software: you are free to change and redistribute it.  There is NO WARRANTY, to the ex‐
       tent permitted by law.

SEE ALSO
       dirname(1), readlink(1)

       Full documentation <https://www.gnu.org/software/coreutils/basename>
       or available locally via: info '(coreutils) basename invocation'

GNU coreutils 9.1                              September 2022                                   BASENAME(1)

## tldr basename
basename

[0m[0mRemove leading directory portions from a path.
More information: https://www.gnu.org/software/coreutils/manual/html_node/basename-invocation.html.

 - [0m[32;23;22;24;25mShow only the file name from a path:
   [33;23;22;24;25mbasename [0mpath/to/file
[0m
 - [0m[32;23;22;24;25mShow only the rightmost directory name from a path:
   [33;23;22;24;25mbasename [0mpath/to/directory
[0m
 - [0m[32;23;22;24;25mShow only the file name from a path, with a suffix removed:
   [33;23;22;24;25mbasename [0mpath/to/file[33;23;22;24;25m [0msuffix
[0m[0m

# bash

## man bash
BASH(1)                                   General Commands Manual                                   BASH(1)

NAME
       bash - GNU Bourne-Again SHell

SYNOPSIS
       bash [options] [command_string | file]

COPYRIGHT
       Bash is Copyright (C) 1989-2022 by the Free Software Foundation, Inc.

DESCRIPTION
       Bash  is an sh-compatible command language interpreter that executes commands read from the standard
       input or from a file.  Bash also incorporates useful features from the Korn and C  shells  (ksh  and
       csh).

       Bash  is  intended  to be a conformant implementation of the Shell and Utilities portion of the IEEE
       POSIX specification (IEEE Standard 1003.1).  Bash can be configured to be  POSIX-conformant  by  de‐
       fault.

OPTIONS
       All  of the single-character shell options documented in the description of the set builtin command,
       including -o, can be used as options when the shell is invoked.  In addition,  bash  interprets  the
       following options when it is invoked:

       -c        If  the  -c  option  is present, then commands are read from the first non-option argument
                 command_string.  If there are arguments after the command_string, the  first  argument  is
                 assigned to $0 and any remaining arguments are assigned to the positional parameters.  The
                 assignment to $0 sets the name of the shell, which is used in warning and error messages.
       -i        If the -i option is present, the shell is interactive.
       -l        Make bash act as if it had been invoked as a login shell (see INVOCATION below).
       -r        If the -r option is present, the shell becomes restricted (see RESTRICTED SHELL below).
       -s        If the -s option is present, or if no arguments remain after option processing, then  com‐
                 mands  are  read from the standard input.  This option allows the positional parameters to
                 be set when invoking an interactive shell or when reading input through a pipe.
       -v        Print shell input lines as they are read.
       -x        Print commands and their arguments as they are executed.
       -D        A list of all double-quoted strings preceded by $  is  printed  on  the  standard  output.
                 These  are the strings that are subject to language translation when the current locale is
                 not C or POSIX.  This implies the -n option; no commands will be executed.
       [-+]O [shopt_option]
                 shopt_option is one of the shell options accepted by the shopt builtin (see SHELL  BUILTIN
                 COMMANDS  below).  If shopt_option is present, -O sets the value of that option; +O unsets
                 it.  If shopt_option is not supplied, the names and values of the shell  options  accepted
                 by  shopt  are printed on the standard output.  If the invocation option is +O, the output
                 is displayed in a format that may be reused as input.
       --        A -- signals the end of options and disables further option processing.  Any arguments af‐
                 ter the -- are treated as filenames and arguments.  An argument of - is equivalent to --.

       Bash  also interprets a number of multi-character options.  These options must appear on the command
       line before the single-character options to be recognized.

       --debugger
              Arrange for the debugger profile to be executed before the shell starts.  Turns  on  extended
              debugging mode (see the description of the extdebug option to the shopt builtin below).
       --dump-po-strings
              Equivalent to -D, but the output is in the GNU gettext po (portable object) file format.
       --dump-strings
              Equivalent to -D.
       --help Display a usage message on standard output and exit successfully.
       --init-file file
       --rcfile file
              Execute  commands  from  file instead of the system wide initialization file /etc/bash.bashrc
              and the standard personal initialization file ~/.bashrc if the shell is interactive (see  IN‐
              VOCATION below).

       --login
              Equivalent to -l.

       --noediting
              Do not use the GNU readline library to read command lines when the shell is interactive.

       --noprofile
              Do  not read either the system-wide startup file /etc/profile or any of the personal initial‐
              ization files ~/.bash_profile, ~/.bash_login, or ~/.profile.  By default,  bash  reads  these
              files when it is invoked as a login shell (see INVOCATION below).

       --norc Do not read and execute the system wide initialization file /etc/bash.bashrc and the personal
              initialization file ~/.bashrc if the shell is interactive.  This option is on by  default  if
              the shell is invoked as sh.

       --posix
              Change  the  behavior  of bash where the default operation differs from the POSIX standard to
              match the standard (posix mode).  See SEE ALSO below for a reference to a document  that  de‐
              tails how posix mode affects bash's behavior.

       --restricted
              The shell becomes restricted (see RESTRICTED SHELL below).

       --verbose
              Equivalent to -v.

       --version
              Show  version  information for this instance of bash on the standard output and exit success‐
              fully.

ARGUMENTS
       If arguments remain after option processing, and neither the -c nor the -s option has been supplied,
       the  first  argument  is assumed to be the name of a file containing shell commands.  If bash is in‐
       voked in this fashion, $0 is set to the name of the file, and the positional parameters are  set  to
       the  remaining arguments.  Bash reads and executes commands from this file, then exits.  Bash's exit
       status is the exit status of the last command executed in the script.  If no commands are  executed,
       the  exit  status is 0.  An attempt is first made to open the file in the current directory, and, if
       no file is found, then the shell searches the directories in PATH for the script.

INVOCATION
       A login shell is one whose first character of argument zero is a -, or one started with the  --login
       option.

       An  interactive shell is one started without non-option arguments (unless -s is specified) and with‐
       out the -c option, whose standard input and error are both connected to terminals (as determined  by
       isatty(3)), or one started with the -i option.  PS1 is set and $- includes i if bash is interactive,
       allowing a shell script or a startup file to test this state.

       The following paragraphs describe how bash executes its startup files.  If any of  the  files  exist
       but  cannot be read, bash reports an error.  Tildes are expanded in filenames as described below un‐
       der Tilde Expansion in the EXPANSION section.

       When bash is invoked as an interactive login shell, or as a non-interactive shell with  the  --login
       option, it first reads and executes commands from the file /etc/profile, if that file exists.  After
       reading that file, it looks for ~/.bash_profile, ~/.bash_login, and ~/.profile, in that  order,  and
       reads  and executes commands from the first one that exists and is readable.  The --noprofile option
       may be used when the shell is started to inhibit this behavior.

       When an interactive login shell exits, or a non-interactive login shell executes  the  exit  builtin
       command, bash reads and executes commands from the file ~/.bash_logout, if it exists.

       When  an  interactive  shell  that is not a login shell is started, bash reads and executes commands
       from /etc/bash.bashrc and ~/.bashrc, if these files exist.  This  may  be  inhibited  by  using  the
       --norc  option.  The --rcfile file option will force bash to read and execute commands from file in‐
       stead of /etc/bash.bashrc and ~/.bashrc.

       When bash is started non-interactively, to run a shell script, for example, it looks for  the  vari‐
       able BASH_ENV in the environment, expands its value if it appears there, and uses the expanded value
       as the name of a file to read and execute.  Bash behaves as if the following command were executed:
              if [ -n "$BASH_ENV" ]; then . "$BASH_ENV"; fi
       but the value of the PATH variable is not used to search for the filename.

       If bash is invoked with the name sh, it tries to mimic the startup behavior of  historical  versions
       of  sh  as  closely as possible, while conforming to the POSIX standard as well.  When invoked as an
       interactive login shell, or a non-interactive shell with the --login option, it  first  attempts  to
       read  and  execute commands from /etc/profile and ~/.profile, in that order.  The --noprofile option
       may be used to inhibit this behavior.  When invoked as an interactive shell with the name  sh,  bash
       looks  for  the variable ENV, expands its value if it is defined, and uses the expanded value as the
       name of a file to read and execute.  Since a shell invoked as sh does not attempt to read  and  exe‐
       cute  commands  from  any other startup files, the --rcfile option has no effect.  A non-interactive
       shell invoked with the name sh does not attempt to read any other startup files.   When  invoked  as
       sh, bash enters posix mode after the startup files are read.

       When  bash  is  started in posix mode, as with the --posix command line option, it follows the POSIX
       standard for startup files.  In this mode, interactive shells expand the ENV variable  and  commands
       are  read  and  executed from the file whose name is the expanded value.  No other startup files are
       read.

       Bash attempts to determine when it is being run with its standard input connected to a network  con‐
       nection,  as  when executed by the historical remote shell daemon, usually rshd, or the secure shell
       daemon sshd.  If bash determines it is being run non-interactively in this fashion, it reads and ex‐
       ecutes commands from /etc/bash.bashrc and ~/.bashrc, if these files exist and are readable.  It will
       not do this if invoked as sh.  The --norc option may be used to inhibit this behavior, and the --rc‐
       file option may be used to force another file to be read, but neither rshd nor sshd generally invoke
       the shell with those options or allow them to be specified.

       If the shell is started with the effective user (group) id not equal to the real  user  (group)  id,
       and the -p option is not supplied, no startup files are read, shell functions are not inherited from
       the environment, the SHELLOPTS, BASHOPTS, CDPATH, and GLOBIGNORE variables, if they  appear  in  the
       environment, are ignored, and the effective user id is set to the real user id.  If the -p option is
       supplied at invocation, the startup behavior is the same, but the effective user id is not reset.

DEFINITIONS
       The following definitions are used throughout the rest of this document.
       blank  A space or tab.
       word   A sequence of characters considered as a single unit by the shell.  Also known as a token.
       name   A word consisting only of alphanumeric characters and underscores, and beginning with an  al‐
              phabetic character or an underscore.  Also referred to as an identifier.
       metacharacter
              A character that, when unquoted, separates words.  One of the following:
              |  & ; ( ) < > space tab newline
       control operator
              A token that performs a control function.  It is one of the following symbols:
              || & && ; ;; ;& ;;& ( ) | |& <newline>

RESERVED WORDS
       Reserved  words  are words that have a special meaning to the shell.  The following words are recog‐
       nized as reserved when unquoted and either the first word of a command (see  SHELL  GRAMMAR  below),
       the  third  word  of a case or select command (only in is valid), or the third word of a for command
       (only in and do are valid):

       ! case  coproc  do done elif else esac fi for function if in select then until while { } time [[ ]]

SHELL GRAMMAR
       This section describes the syntax of the various forms of shell commands.

   Simple Commands
       A simple command is a sequence of optional variable assignments followed  by  blank-separated  words
       and  redirections, and terminated by a control operator.  The first word specifies the command to be
       executed, and is passed as argument zero.  The remaining words are passed as arguments  to  the  in‐
       voked command.

       The  return  value  of a simple command is its exit status, or 128+n if the command is terminated by
       signal n.

   Pipelines
       A pipeline is a sequence of one or more commands separated by one of the control operators | or  |&.
       The format for a pipeline is:

              [time [-p]] [ ! ] command1 [ [|⎪|&] command2 ... ]

       The  standard  output  of  command1 is connected via a pipe to the standard input of command2.  This
       connection is performed before any redirections specified by the  command1(see  REDIRECTION  below).
       If  |&  is used, command1's standard error, in addition to its standard output, is connected to com‐
       mand2's standard input through the pipe; it is shorthand for 2>&1 |.  This implicit  redirection  of
       the standard error to the standard output is performed after any redirections specified by command1.

       The  return  status of a pipeline is the exit status of the last command, unless the pipefail option
       is enabled.  If pipefail is enabled, the pipeline's return status is the value of the  last  (right‐
       most) command to exit with a non-zero status, or zero if all commands exit successfully.  If the re‐
       served word !  precedes a pipeline, the exit status of that pipeline is the logical negation of  the
       exit  status  as described above.  The shell waits for all commands in the pipeline to terminate be‐
       fore returning a value.

       If the time reserved word precedes a pipeline, the elapsed as well as user and system time  consumed
       by its execution are reported when the pipeline terminates.  The -p option changes the output format
       to that specified by POSIX.  When the shell is in posix mode, it does not recognize time  as  a  re‐
       served  word  if  the  next token begins with a `-'.  The TIMEFORMAT variable may be set to a format
       string that specifies how the timing information should be displayed; see the description  of  TIME‐
       FORMAT under Shell Variables below.

       When  the  shell  is in posix mode, time may be followed by a newline.  In this case, the shell dis‐
       plays the total user and system time consumed by the shell and its children.  The  TIMEFORMAT  vari‐
       able may be used to specify the format of the time information.

       Each  command in a multi-command pipeline, where pipes are created, is executed in a subshell, which
       is a separate process.  See COMMAND EXECUTION ENVIRONMENT for a description of subshells and a  sub‐
       shell  environment.   If the lastpipe option is enabled using the shopt builtin (see the description
       of shopt below), the last element of a pipeline may be run by the shell process when job control  is
       not active.

   Lists
       A list is a sequence of one or more pipelines separated by one of the operators ;, &, &&, or ||, and
       optionally terminated by one of ;, &, or <newline>.

       Of these list operators, && and || have equal precedence, followed by ;  and  &,  which  have  equal
       precedence.

       A sequence of one or more newlines may appear in a list instead of a semicolon to delimit commands.

       If  a  command  is terminated by the control operator &, the shell executes the command in the back‐
       ground in a subshell.  The shell does not wait for the command to finish, and the return  status  is
       0.   These are referred to as asynchronous commands.  Commands separated by a ; are executed sequen‐
       tially; the shell waits for each command to terminate in turn.  The return status is the exit status
       of the last command executed.

       AND  and  OR  lists are sequences of one or more pipelines separated by the && and || control opera‐
       tors, respectively.  AND and OR lists are executed with left associativity.  An  AND  list  has  the
       form

              command1 && command2

       command2 is executed if, and only if, command1 returns an exit status of zero (success).

       An OR list has the form

              command1 || command2

       command2 is executed if, and only if, command1 returns a non-zero exit status.  The return status of
       AND and OR lists is the exit status of the last command executed in the list.

   Compound Commands
       A compound command is one of the following.  In most cases a list in a command's description may  be
       separated  from the rest of the command by one or more newlines, and may be followed by a newline in
       place of a semicolon.

       (list) list is executed in a subshell (see COMMAND EXECUTION ENVIRONMENT below for a description  of
              a  subshell  environment).  Variable assignments and builtin commands that affect the shell's
              environment do not remain in effect after the command completes.  The return  status  is  the
              exit status of list.

       { list; }
              list  is  simply  executed  in the current shell environment.  list must be terminated with a
              newline or semicolon.  This is known as a group command.  The return status is the exit  sta‐
              tus  of  list.   Note  that unlike the metacharacters ( and ), { and } are reserved words and
              must occur where a reserved word is permitted to be recognized.  Since they do  not  cause  a
              word break, they must be separated from list by whitespace or another shell metacharacter.

       ((expression))
              The  expression  is evaluated according to the rules described below under ARITHMETIC EVALUA‐
              TION.  If the value of the expression is non-zero, the return status is 0; otherwise the  re‐
              turn  status  is 1.  The expression undergoes the same expansions as if it were within double
              quotes, but double quote characters in expression are not treated specially and are removed.

       [[ expression ]]
              Return a status of 0 or 1 depending on the evaluation of the conditional  expression  expres‐
              sion.   Expressions  are  composed of the primaries described below under CONDITIONAL EXPRES‐
              SIONS.  The words between the [[ and ]] do not undergo word splitting and pathname expansion.
              The  shell  performs tilde expansion, parameter and variable expansion, arithmetic expansion,
              command substitution, process substitution, and quote removal on those words (the  expansions
              that would occur if the words were enclosed in double quotes).  Conditional operators such as
              -f must be unquoted to be recognized as primaries.

              When used with [[, the < and > operators sort lexicographically using the current locale.

       See the description of the test builtin command (section SHELL BUILTIN COMMANDS below) for the  han‐
       dling of parameters (i.e.  missing parameters).

       When  the == and != operators are used, the string to the right of the operator is considered a pat‐
       tern and matched according to the rules described below under Pattern Matching, as  if  the  extglob
       shell  option were enabled.  The = operator is equivalent to ==.  If the nocasematch shell option is
       enabled, the match is performed without regard to the case of  alphabetic  characters.   The  return
       value is 0 if the string matches (==) or does not match (!=) the pattern, and 1 otherwise.  Any part
       of the pattern may be quoted to force the quoted portion to be matched as a string.

       An additional binary operator, =~, is available, with the same precedence as == and !=.  When it  is
       used,  the string to the right of the operator is considered a POSIX extended regular expression and
       matched accordingly (using the POSIX regcomp and regexec interfaces usually described in  regex(3)).
       The return value is 0 if the string matches the pattern, and 1 otherwise.  If the regular expression
       is syntactically incorrect, the conditional expression's return value  is  2.   If  the  nocasematch
       shell option is enabled, the match is performed without regard to the case of alphabetic characters.
       If any part of the pattern is quoted, the quoted portion is matched  literally.   This  means  every
       character in the quoted portion matches itself, instead of having any special pattern matching mean‐
       ing.  If the pattern is stored in a shell variable, quoting the variable expansion forces the entire
       pattern  to be matched literally.  Treat bracket expressions in regular expressions carefully, since
       normal quoting and pattern characters lose their meanings between brackets.

       The pattern will match if it matches any part of the string.  Anchor the pattern using the ^  and  $
       regular  expression  operators  to force it to match the entire string.  The array variable BASH_RE‐
       MATCH records which parts of the string matched the pattern.  The element of BASH_REMATCH with index
       0  contains the portion of the string matching the entire regular expression.  Substrings matched by
       parenthesized subexpressions within the regular expression are saved in the  remaining  BASH_REMATCH
       indices.  The  element  of  BASH_REMATCH  with index n is the portion of the string matching the nth
       parenthesized subexpression.  Bash sets BASH_REMATCH in the global scope; declaring it  as  a  local
       variable will lead to unexpected results.

       Expressions may be combined using the following operators, listed in decreasing order of precedence:

              ( expression )
                     Returns  the  value of expression.  This may be used to override the normal precedence
                     of operators.
              ! expression
                     True if expression is false.
              expression1 && expression2
                     True if both expression1 and expression2 are true.
              expression1 || expression2
                     True if either expression1 or expression2 is true.

              The && and || operators do not evaluate expression2 if the value of expression1 is sufficient
              to determine the return value of the entire conditional expression.

       for name [ [ in [ word ... ] ] ; ] do list ; done
              The list of words following in is expanded, generating a list of items.  The variable name is
              set to each element of this list in turn, and list is executed each time.  If the in word  is
              omitted,  the  for  command executes list once for each positional parameter that is set (see
              PARAMETERS below).  The return status is the exit status of the last command  that  executes.
              If  the  expansion  of  the items following in results in an empty list, no commands are exe‐
              cuted, and the return status is 0.

       for (( expr1 ; expr2 ; expr3 )) ; do list ; done
              First, the arithmetic expression expr1 is evaluated according to the  rules  described  below
              under  ARITHMETIC  EVALUATION.   The arithmetic expression expr2 is then evaluated repeatedly
              until it evaluates to zero.  Each time expr2 evaluates to a non-zero value, list is  executed
              and  the  arithmetic expression expr3 is evaluated.  If any expression is omitted, it behaves
              as if it evaluates to 1.  The return value is the exit status of the  last  command  in  list
              that is executed, or false if any of the expressions is invalid.

       select name [ in word ] ; do list ; done
              The  list  of  words following in is expanded, generating a list of items, and the set of ex‐
              panded words is printed on the standard error, each preceded by a number.  If the in word  is
              omitted,  the positional parameters are printed (see PARAMETERS below).  select then displays
              the PS3 prompt and reads a line from the standard input.  If the line consists  of  a  number
              corresponding  to one of the displayed words, then the value of name is set to that word.  If
              the line is empty, the words and prompt are displayed again.  If EOF is read, the select com‐
              mand  completes and returns 1.  Any other value read causes name to be set to null.  The line
              read is saved in the variable REPLY.  The list is executed after each selection until a break
              command  is  executed.  The exit status of select is the exit status of the last command exe‐
              cuted in list, or zero if no commands were executed.

       case word in [ [(] pattern [ | pattern ] ... ) list ;; ] ... esac
              A case command first expands word, and tries to match it against each pattern in turn,  using
              the  matching rules described under Pattern Matching below.  The word is expanded using tilde
              expansion, parameter and variable  expansion,  arithmetic  expansion,  command  substitution,
              process substitution and quote removal.  Each pattern examined is expanded using tilde expan‐
              sion, parameter and variable expansion, arithmetic expansion, command  substitution,  process
              substitution,  and  quote  removal.  If the nocasematch shell option is enabled, the match is
              performed without regard to the case of alphabetic characters.  When a match  is  found,  the
              corresponding  list  is  executed.  If the ;; operator is used, no subsequent matches are at‐
              tempted after the first pattern match.  Using ;& in place of ;; causes execution to  continue
              with  the list associated with the next set of patterns.  Using ;;& in place of ;; causes the
              shell to test the next pattern list in the statement, if any, and execute any associated list
              on a successful match, continuing the case statement execution as if the pattern list had not
              matched.  The exit status is zero if no pattern matches.  Otherwise, it is the exit status of
              the last command executed in list.

       if list; then list; [ elif list; then list; ] ... [ else list; ] fi
              The  if list is executed.  If its exit status is zero, the then list is executed.  Otherwise,
              each elif list is executed in turn, and if its exit status is zero,  the  corresponding  then
              list  is  executed  and  the  command  completes.   Otherwise,  the else list is executed, if
              present.  The exit status is the exit status of the last command executed, or zero if no con‐
              dition tested true.

       while list-1; do list-2; done
       until list-1; do list-2; done
              The  while  command  continuously executes the list list-2 as long as the last command in the
              list list-1 returns an exit status of zero.  The until command is identical to the while com‐
              mand,  except  that  the  test  is negated: list-2 is executed as long as the last command in
              list-1 returns a non-zero exit status.  The exit status of the while and  until  commands  is
              the exit status of the last command executed in list-2, or zero if none was executed.

   Coprocesses
       A  coprocess is a shell command preceded by the coproc reserved word.  A coprocess is executed asyn‐
       chronously in a subshell, as if the command had been terminated with the & control operator, with  a
       two-way pipe established between the executing shell and the coprocess.

       The syntax for a coprocess is:

              coproc [NAME] command [redirections]

       This  creates  a coprocess named NAME.  command may be either a simple command or a compound command
       (see above).  NAME is a shell variable name.  If NAME is not supplied, the default name is COPROC.

       The recommended form to use for a coprocess is

              coproc NAME { command [redirections]; }

       This form is recommended because simple commands result in the coprocess always being named  COPROC,
       and it is simpler to use and more complete than the other compound commands.

       If  command  is  a  compound command, NAME is optional. The word following coproc determines whether
       that word is interpreted as a variable name: it is interpreted as NAME if it is not a reserved  word
       that introduces a compound command.  If command is a simple command, NAME is not allowed; this is to
       avoid confusion between NAME and the first word of the simple command.

       When the coprocess is executed, the shell creates an array variable (see Arrays below) named NAME in
       the  context  of  the  executing shell.  The standard output of command is connected via a pipe to a
       file descriptor in the executing shell, and that file descriptor is assigned to NAME[0].  The  stan‐
       dard  input of command is connected via a pipe to a file descriptor in the executing shell, and that
       file descriptor is assigned to NAME[1].  This pipe is established before any redirections  specified
       by  the command (see REDIRECTION below).  The file descriptors can be utilized as arguments to shell
       commands and redirections using standard word expansions.  Other than those created to execute  com‐
       mand and process substitutions, the file descriptors are not available in subshells.

       The  process ID of the shell spawned to execute the coprocess is available as the value of the vari‐
       able NAME_PID.  The wait builtin command may be used to wait for the coprocess to terminate.

       Since the coprocess is created as an asynchronous command, the coproc command  always  returns  suc‐
       cess.  The return status of a coprocess is the exit status of command.

   Shell Function Definitions
       A  shell  function is an object that is called like a simple command and executes a compound command
       with a new set of positional parameters.  Shell functions are declared as follows:

       fname () compound-command [redirection]
       function fname [()] compound-command [redirection]
              This defines a function named fname.  The reserved word function is optional.  If  the  func‐
              tion  reserved  word  is supplied, the parentheses are optional.  The body of the function is
              the compound command compound-command (see Compound Commands above).  That command is usually
              a  list  of  commands  between { and }, but may be any command listed under Compound Commands
              above.  If the function reserved word is used, but the  parentheses  are  not  supplied,  the
              braces are recommended.  compound-command is executed whenever fname is specified as the name
              of a simple command.  When in posix mode, fname must be a valid shell name and may not be the
              name  of  one of the POSIX special builtins.  In default mode, a function name can be any un‐
              quoted shell word that does not contain $.  Any redirections (see REDIRECTION  below)  speci‐
              fied when a function is defined are performed when the function is executed.  The exit status
              of a function definition is zero unless a syntax error occurs or a readonly function with the
              same name already exists.  When executed, the exit status of a function is the exit status of
              the last command executed in the body.  (See FUNCTIONS below.)

COMMENTS
       In a non-interactive shell, or an interactive shell in which the interactive_comments option to  the
       shopt  builtin  is  enabled  (see SHELL BUILTIN COMMANDS below), a word beginning with # causes that
       word and all remaining characters on that line to be ignored.  An interactive shell without the  in‐
       teractive_comments option enabled does not allow comments.  The interactive_comments option is on by
       default in interactive shells.

QUOTING
       Quoting is used to remove the special meaning of certain characters or words to the shell.   Quoting
       can  be used to disable special treatment for special characters, to prevent reserved words from be‐
       ing recognized as such, and to prevent parameter expansion.

       Each of the metacharacters listed above under DEFINITIONS has special meaning to the shell and  must
       be quoted if it is to represent itself.

       When the command history expansion facilities are being used (see HISTORY EXPANSION below), the his‐
       tory expansion character, usually !, must be quoted to prevent history expansion.

       There are three quoting mechanisms: the escape character, single quotes, and double quotes.

       A non-quoted backslash (\) is the escape character.  It preserves the  literal  value  of  the  next
       character  that  follows,  with  the  exception of <newline>.  If a \<newline> pair appears, and the
       backslash is not itself quoted, the \<newline> is treated as a line continuation (that is, it is re‐
       moved from the input stream and effectively ignored).

       Enclosing  characters  in  single  quotes  preserves  the literal value of each character within the
       quotes.  A single quote may not occur between single quotes, even when preceded by a backslash.

       Enclosing characters in double quotes preserves the literal  value  of  all  characters  within  the
       quotes, with the exception of $, `, \, and, when history expansion is enabled, !.  When the shell is
       in posix mode, the ! has no special meaning within double quotes, even when history expansion is en‐
       abled.  The characters $ and ` retain their special meaning within double quotes.  The backslash re‐
       tains its special meaning only when followed by one of the following characters:  $,  `,  ",  \,  or
       <newline>.   A double quote may be quoted within double quotes by preceding it with a backslash.  If
       enabled, history expansion will be performed unless an !  appearing in double quotes is escaped  us‐
       ing a backslash.  The backslash preceding the !  is not removed.

       The special parameters * and @ have special meaning when in double quotes (see PARAMETERS below).

       Character  sequences  of  the form $'string' are treated as a special variant of single quotes.  The
       sequence expands to string, with backslash-escaped characters in string replaced as specified by the
       ANSI C standard.  Backslash escape sequences, if present, are decoded as follows:
              \a     alert (bell)
              \b     backspace
              \e
              \E     an escape character
              \f     form feed
              \n     new line
              \r     carriage return
              \t     horizontal tab
              \v     vertical tab
              \\     backslash
              \'     single quote
              \"     double quote
              \?     question mark
              \nnn   the eight-bit character whose value is the octal value nnn (one to three octal digits)
              \xHH   the  eight-bit  character whose value is the hexadecimal value HH (one or two hex dig‐
                     its)
              \uHHHH the Unicode (ISO/IEC 10646) character whose value is the hexadecimal value  HHHH  (one
                     to four hex digits)
              \UHHHHHHHH
                     the  Unicode  (ISO/IEC  10646) character whose value is the hexadecimal value HHHHHHHH
                     (one to eight hex digits)
              \cx    a control-x character

       The expanded result is single-quoted, as if the dollar sign had not been present.

       A double-quoted string preceded by a dollar sign ($"string") will cause the string to be  translated
       according  to  the  current locale.  The gettext infrastructure performs the lookup and translation,
       using the LC_MESSAGES, TEXTDOMAINDIR, and TEXTDOMAIN shell variables.  If the current locale is C or
       POSIX,  if  there are no translations available, or if the string is not translated, the dollar sign
       is ignored.  This is a form of double quoting, so  the  string  remains  double-quoted  by  default,
       whether  or  not it is translated and replaced.  If the noexpand_translation option is enabled using
       the shopt builtin, translated strings are single-quoted instead of double-quoted.  See the  descrip‐
       tion of shopt below under SHELLBUILTINCOMMANDS.

PARAMETERS
       A  parameter  is  an  entity  that stores values.  It can be a name, a number, or one of the special
       characters listed below under Special Parameters.  A variable is a parameter denoted by a  name.   A
       variable has a value and zero or more attributes.  Attributes are assigned using the declare builtin
       command (see declare below in SHELL BUILTIN COMMANDS).

       A parameter is set if it has been assigned a value.  The null string is a valid value.  Once a vari‐
       able is set, it may be unset only by using the unset builtin command (see SHELL BUILTIN COMMANDS be‐
       low).

       A variable may be assigned to by a statement of the form

              name=[value]

       If value is not given, the variable is assigned the null string.  All values  undergo  tilde  expan‐
       sion,  parameter  and  variable expansion, command substitution, arithmetic expansion, and quote re‐
       moval (see EXPANSION below).  If the variable has its integer attribute set, then value is evaluated
       as an arithmetic expression even if the $((...)) expansion is not used (see Arithmetic Expansion be‐
       low).  Word splitting and pathname expansion are not performed.  Assignment statements may also  ap‐
       pear as arguments to the alias, declare, typeset, export, readonly, and local builtin commands (dec‐
       laration commands).  When in posix mode, these builtins may appear in a command after  one  or  more
       instances of the command builtin and retain these assignment statement properties.

       In  the  context where an assignment statement is assigning a value to a shell variable or array in‐
       dex, the += operator can be used to append to or add to the variable's  previous  value.   This  in‐
       cludes  arguments to builtin commands such as declare that accept assignment statements (declaration
       commands).  When += is applied to a variable for which the integer attribute has been set, value  is
       evaluated as an arithmetic expression and added to the variable's current value, which is also eval‐
       uated.  When += is applied to an array variable using compound assignment (see  Arrays  below),  the
       variable's  value is not unset (as it is when using =), and new values are appended to the array be‐
       ginning at one greater than the array's maximum index (for indexed arrays) or  added  as  additional
       key-value  pairs  in  an  associative array.  When applied to a string-valued variable, value is ex‐
       panded and appended to the variable's value.

       A variable can be assigned the nameref attribute using the -n option to the declare or local builtin
       commands  (see  the  descriptions of declare and local below) to create a nameref, or a reference to
       another variable.  This allows variables to be manipulated indirectly.  Whenever the  nameref  vari‐
       able is referenced, assigned to, unset, or has its attributes modified (other than using or changing
       the nameref attribute itself), the operation is actually performed on the variable specified by  the
       nameref  variable's value.  A nameref is commonly used within shell functions to refer to a variable
       whose name is passed as an argument to the function.  For instance, if a variable name is passed  to
       a shell function as its first argument, running
              declare -n ref=$1
       inside  the  function  creates a nameref variable ref whose value is the variable name passed as the
       first argument.  References and assignments to ref, and changes to its attributes,  are  treated  as
       references,  assignments,  and  attribute modifications to the variable whose name was passed as $1.
       If the control variable in a for loop has the nameref attribute, the list of words can be a list  of
       shell  variables,  and a name reference will be established for each word in the list, in turn, when
       the loop is executed.  Array variables cannot be given  the  nameref  attribute.   However,  nameref
       variables  can reference array variables and subscripted array variables.  Namerefs can be unset us‐
       ing the -n option to the unset builtin.  Otherwise, if unset is executed with the name of a  nameref
       variable as an argument, the variable referenced by the nameref variable will be unset.

   Positional Parameters
       A  positional parameter is a parameter denoted by one or more digits, other than the single digit 0.
       Positional parameters are assigned from the shell's arguments when it is invoked, and may  be  reas‐
       signed  using the set builtin command.  Positional parameters may not be assigned to with assignment
       statements.  The positional parameters are temporarily replaced when a shell  function  is  executed
       (see FUNCTIONS below).

       When  a positional parameter consisting of more than a single digit is expanded, it must be enclosed
       in braces (see EXPANSION below).

   Special Parameters
       The shell treats several parameters specially.  These parameters may only be referenced;  assignment
       to them is not allowed.
       *      Expands  to  the  positional parameters, starting from one.  When the expansion is not within
              double quotes, each positional parameter expands to a separate word.  In contexts where it is
              performed,  those  words  are subject to further word splitting and pathname expansion.  When
              the expansion occurs within double quotes, it expands to a single word with the value of each
              parameter  separated  by  the  first character of the IFS special variable.  That is, "$*" is
              equivalent to "$1c$2c...", where c is the first character of the value of the  IFS  variable.
              If  IFS is unset, the parameters are separated by spaces.  If IFS is null, the parameters are
              joined without intervening separators.
       @      Expands to the positional parameters, starting from one.  In contexts where word splitting is
              performed,  this  expands  each positional parameter to a separate word; if not within double
              quotes, these words are subject to word splitting.  In contexts where word splitting  is  not
              performed, this expands to a single word with each positional parameter separated by a space.
              When the expansion occurs within double quotes, each parameter expands to  a  separate  word.
              That  is, "$@" is equivalent to "$1" "$2" ...  If the double-quoted expansion occurs within a
              word, the expansion of the first parameter is joined with the beginning part of the  original
              word,  and  the  expansion of the last parameter is joined with the last part of the original
              word.  When there are no positional parameters, "$@" and $@ expand to nothing (i.e., they are
              removed).
       #      Expands to the number of positional parameters in decimal.
       ?      Expands to the exit status of the most recently executed foreground pipeline.
       -      Expands to the current option flags as specified upon invocation, by the set builtin command,
              or those set by the shell itself (such as the -i option).
       $      Expands to the process ID of the shell. In a subshell, it expands to the process  ID  of  the
              current shell, not the subshell.
       !      Expands  to  the process ID of the job most recently placed into the background, whether exe‐
              cuted as an asynchronous command or using the bg builtin (see JOB CONTROL below).
       0      Expands to the name of the shell or shell script.  This is set at shell  initialization.   If
              bash  is  invoked  with  a  file of commands, $0 is set to the name of that file.  If bash is
              started with the -c option, then $0 is set to the first argument after the string to be  exe‐
              cuted, if one is present.  Otherwise, it is set to the filename used to invoke bash, as given
              by argument zero.

   Shell Variables
       The following variables are set by the shell:

       _      At shell startup, set to the pathname used to invoke the shell or shell script being executed
              as passed in the environment or argument list.  Subsequently, expands to the last argument to
              the previous simple command executed in the foreground, after expansion.   Also  set  to  the
              full  pathname used to invoke each command executed and placed in the environment exported to
              that command.  When checking mail, this parameter holds the name of the mail  file  currently
              being checked.
       BASH   Expands to the full filename used to invoke this instance of bash.
       BASHOPTS
              A  colon-separated  list of enabled shell options.  Each word in the list is a valid argument
              for the -s option to the shopt builtin command (see SHELL BUILTIN COMMANDS below).   The  op‐
              tions  appearing  in  BASHOPTS are those reported as on by shopt.  If this variable is in the
              environment when bash starts up, each shell option in the list will be enabled before reading
              any startup files.  This variable is read-only.
       BASHPID
              Expands  to  the  process ID of the current bash process.  This differs from $$ under certain
              circumstances, such as subshells that do not require bash to be re-initialized.   Assignments
              to  BASHPID have no effect.  If BASHPID is unset, it loses its special properties, even if it
              is subsequently reset.
       BASH_ALIASES
              An associative array variable whose members correspond to the internal  list  of  aliases  as
              maintained by the alias builtin.  Elements added to this array appear in the alias list; how‐
              ever, unsetting array elements currently does not cause aliases to be removed from the  alias
              list.   If BASH_ALIASES is unset, it loses its special properties, even if it is subsequently
              reset.
       BASH_ARGC
              An array variable whose values are the number of parameters in each frame of the current bash
              execution  call stack.  The number of parameters to the current subroutine (shell function or
              script executed with . or source) is at the top of the stack.  When a subroutine is executed,
              the number of parameters passed is pushed onto BASH_ARGC.  The shell sets BASH_ARGC only when
              in extended debugging mode (see the description of the extdebug option to the  shopt  builtin
              below).   Setting  extdebug  after  the shell has started to execute a script, or referencing
              this variable when extdebug is not set, may result in inconsistent values.
       BASH_ARGV
              An array variable containing all of the parameters in the current bash execution call  stack.
              The final parameter of the last subroutine call is at the top of the stack; the first parame‐
              ter of the initial call is at the bottom.  When a subroutine is executed, the parameters sup‐
              plied  are  pushed  onto BASH_ARGV.  The shell sets BASH_ARGV only when in extended debugging
              mode (see the description of the extdebug option to the shopt builtin below).  Setting extde‐
              bug after the shell has started to execute a script, or referencing this variable when extde‐
              bug is not set, may result in inconsistent values.
       BASH_ARGV0
              When referenced, this variable expands to the name of the shell or shell script (identical to
              $0;  see  the description of special parameter 0 above).  Assignment to BASH_ARGV0 causes the
              value assigned to also be assigned to $0.  If BASH_ARGV0 is unset, it loses its special prop‐
              erties, even if it is subsequently reset.
       BASH_CMDS
              An associative array variable whose members correspond to the internal hash table of commands
              as maintained by the hash builtin.  Elements added to this array appear in  the  hash  table;
              however,  unsetting  array elements currently does not cause command names to be removed from
              the hash table.  If BASH_CMDS is unset, it loses its special properties, even if it is subse‐
              quently reset.
       BASH_COMMAND
              The command currently being executed or about to be executed, unless the shell is executing a
              command as the result of a trap, in which case it is the command executing at the time of the
              trap.   If BASH_COMMAND is unset, it loses its special properties, even if it is subsequently
              reset.
       BASH_EXECUTION_STRING
              The command argument to the -c invocation option.
       BASH_LINENO
              An array variable whose members are the line numbers in source files where each corresponding
              member  of  FUNCNAME  was  invoked.  ${BASH_LINENO[$i]} is the line number in the source file
              (${BASH_SOURCE[$i+1]}) where ${FUNCNAME[$i]} was called (or  ${BASH_LINENO[$i-1]}  if  refer‐
              enced within another shell function).  Use LINENO to obtain the current line number.
       BASH_LOADABLES_PATH
              A  colon-separated  list  of  directories  in  which the shell looks for dynamically loadable
              builtins specified by the enable command.
       BASH_REMATCH
              An array variable whose members are assigned by the =~ binary operator to the [[  conditional
              command.   The  element with index 0 is the portion of the string matching the entire regular
              expression.  The element with index n is the portion of the string matching the nth parenthe‐
              sized subexpression.
       BASH_SOURCE
              An  array variable whose members are the source filenames where the corresponding shell func‐
              tion names in the FUNCNAME array variable are defined.  The shell function ${FUNCNAME[$i]} is
              defined in the file ${BASH_SOURCE[$i]} and called from ${BASH_SOURCE[$i+1]}.
       BASH_SUBSHELL
              Incremented by one within each subshell or subshell environment when the shell begins execut‐
              ing in that environment.  The initial value is 0.  If BASH_SUBSHELL is unset,  it  loses  its
              special properties, even if it is subsequently reset.
       BASH_VERSINFO
              A  readonly  array variable whose members hold version information for this instance of bash.
              The values assigned to the array members are as follows:
              BASH_VERSINFO[0]        The major version number (the release).
              BASH_VERSINFO[1]        The minor version number (the version).
              BASH_VERSINFO[2]        The patch level.
              BASH_VERSINFO[3]        The build version.
              BASH_VERSINFO[4]        The release status (e.g., beta1).
              BASH_VERSINFO[5]        The value of MACHTYPE.
       BASH_VERSION
              Expands to a string describing the version of this instance of bash.
       COMP_CWORD
              An index into ${COMP_WORDS} of the word containing the current cursor position.   This  vari‐
              able  is  available only in shell functions invoked by the programmable completion facilities
              (see Programmable Completion below).
       COMP_KEY
              The key (or final key of a key sequence) used to invoke the current completion function.
       COMP_LINE
              The current command line.  This variable is available only in shell  functions  and  external
              commands  invoked  by the programmable completion facilities (see Programmable Completion be‐
              low).
       COMP_POINT
              The index of the current cursor position relative to the beginning of  the  current  command.
              If  the current cursor position is at the end of the current command, the value of this vari‐
              able is equal to ${#COMP_LINE}.  This variable is available only in shell functions  and  ex‐
              ternal  commands  invoked by the programmable completion facilities (see Programmable Comple‐
              tion below).
       COMP_TYPE
              Set to an integer value corresponding to the type of completion attempted that caused a  com‐
              pletion  function  to be called: TAB, for normal completion, ?, for listing completions after
              successive tabs, !, for listing alternatives on partial word completion, @, to  list  comple‐
              tions  if  the word is not unmodified, or %, for menu completion.  This variable is available
              only in shell functions and external commands invoked by the programmable completion  facili‐
              ties (see Programmable Completion below).
       COMP_WORDBREAKS
              The  set  of  characters  that the readline library treats as word separators when performing
              word completion.  If COMP_WORDBREAKS is unset, it loses its special properties, even if it is
              subsequently reset.
       COMP_WORDS
              An  array  variable (see Arrays below) consisting of the individual words in the current com‐
              mand line.  The line is split into words as readline would split it, using COMP_WORDBREAKS as
              described  above.  This variable is available only in shell functions invoked by the program‐
              mable completion facilities (see Programmable Completion below).
       COPROC An array variable (see Arrays below) created to hold the file descriptors for output from and
              input to an unnamed coprocess (see Coprocesses above).
       DIRSTACK
              An  array variable (see Arrays below) containing the current contents of the directory stack.
              Directories appear in the stack in the order they are displayed by the dirs builtin.  Assign‐
              ing to members of this array variable may be used to modify directories already in the stack,
              but the pushd and popd builtins must be used to add and remove  directories.   Assignment  to
              this variable will not change the current directory.  If DIRSTACK is unset, it loses its spe‐
              cial properties, even if it is subsequently reset.
       EPOCHREALTIME
              Each time this parameter is referenced, it expands to the number of seconds  since  the  Unix
              Epoch  (see time(3)) as a floating point value with micro-second granularity.  Assignments to
              EPOCHREALTIME are ignored.  If EPOCHREALTIME is unset, it loses its special properties,  even
              if it is subsequently reset.
       EPOCHSECONDS
              Each  time  this  parameter is referenced, it expands to the number of seconds since the Unix
              Epoch (see time(3)).  Assignments to EPOCHSECONDS are ignored.  If EPOCHSECONDS is unset,  it
              loses its special properties, even if it is subsequently reset.
       EUID   Expands  to  the  effective  user ID of the current user, initialized at shell startup.  This
              variable is readonly.
       FUNCNAME
              An array variable containing the names of all shell functions currently in the execution call
              stack.   The element with index 0 is the name of any currently-executing shell function.  The
              bottom-most element (the one with the highest index) is "main".  This  variable  exists  only
              when  a shell function is executing.  Assignments to FUNCNAME have no effect.  If FUNCNAME is
              unset, it loses its special properties, even if it is subsequently reset.

              This variable can be used with BASH_LINENO and BASH_SOURCE.  Each  element  of  FUNCNAME  has
              corresponding  elements  in  BASH_LINENO and BASH_SOURCE to describe the call stack.  For in‐
              stance, ${FUNCNAME[$i]}  was  called  from  the  file  ${BASH_SOURCE[$i+1]}  at  line  number
              ${BASH_LINENO[$i]}.   The  caller builtin displays the current call stack using this informa‐
              tion.
       GROUPS An array variable containing the list of groups of which the current user is a  member.   As‐
              signments  to  GROUPS  have  no effect.  If GROUPS is unset, it loses its special properties,
              even if it is subsequently reset.
       HISTCMD
              The history number, or index in the history list, of the  current  command.   Assignments  to
              HISTCMD  are  ignored.   If  HISTCMD is unset, it loses its special properties, even if it is
              subsequently reset.
       HOSTNAME
              Automatically set to the name of the current host.
       HOSTTYPE
              Automatically set to a string that uniquely describes the type of machine on  which  bash  is
              executing.  The default is system-dependent.
       LINENO Each  time  this parameter is referenced, the shell substitutes a decimal number representing
              the current sequential line number (starting with 1) within a script or function.   When  not
              in a script or function, the value substituted is not guaranteed to be meaningful.  If LINENO
              is unset, it loses its special properties, even if it is subsequently reset.
       MACHTYPE
              Automatically set to a string that fully describes the system type on which bash  is  execut‐
              ing, in the standard GNU cpu-company-system format.  The default is system-dependent.
       MAPFILE
              An  array  variable  (see  Arrays below) created to hold the text read by the mapfile builtin
              when no variable name is supplied.
       OLDPWD The previous working directory as set by the cd command.
       OPTARG The value of the last option argument processed by the getopts  builtin  command  (see  SHELL
              BUILTIN COMMANDS below).
       OPTIND The  index  of  the  next  argument to be processed by the getopts builtin command (see SHELL
              BUILTIN COMMANDS below).
       OSTYPE Automatically set to a string that describes the operating system on which bash is executing.
              The default is system-dependent.
       PIPESTATUS
              An  array  variable  (see Arrays below) containing a list of exit status values from the pro‐
              cesses in the most-recently-executed foreground pipeline (which may  contain  only  a  single
              command).
       PPID   The process ID of the shell's parent.  This variable is readonly.
       PWD    The current working directory as set by the cd command.
       RANDOM Each  time  this parameter is referenced, it expands to a random integer between 0 and 32767.
              Assigning a value to RANDOM initializes (seeds) the sequence of random numbers.  If RANDOM is
              unset, it loses its special properties, even if it is subsequently reset.
       READLINE_ARGUMENT
              Any  numeric argument given to a readline command that was defined using "bind -x" (see SHELL
              BUILTIN COMMANDS below) when it was invoked.
       READLINE_LINE
              The contents of the readline line buffer, for use with "bind -x" (see SHELL BUILTIN  COMMANDS
              below).
       READLINE_MARK
              The  position  of  the mark (saved insertion point) in the readline line buffer, for use with
              "bind -x" (see SHELL BUILTIN COMMANDS below).  The characters between the insertion point and
              the mark are often called the region.
       READLINE_POINT
              The  position of the insertion point in the readline line buffer, for use with "bind -x" (see
              SHELL BUILTIN COMMANDS below).
       REPLY  Set to the line of input read by the read builtin command when no arguments are supplied.
       SECONDS
              Each time this parameter is referenced, it expands to the number of seconds since shell invo‐
              cation.   If a value is assigned to SECONDS, the value returned upon subsequent references is
              the number of seconds since the assignment plus the value assigned.  The number of seconds at
              shell invocation and the current time are always determined by querying the system clock.  If
              SECONDS is unset, it loses its special properties, even if it is subsequently reset.
       SHELLOPTS
              A colon-separated list of enabled shell options.  Each word in the list is a  valid  argument
              for the -o option to the set builtin command (see SHELL BUILTIN COMMANDS below).  The options
              appearing in SHELLOPTS are those reported as on by set -o.  If this variable is in the  envi‐
              ronment when bash starts up, each shell option in the list will be enabled before reading any
              startup files.  This variable is read-only.
       SHLVL  Incremented by one each time an instance of bash is started.
       SRANDOM
              This variable expands to a 32-bit pseudo-random number each time it is referenced. The random
              number  generator  is  not linear on systems that support /dev/urandom or arc4random, so each
              returned number has no relationship to the numbers preceding it.  The random number generator
              cannot  be  seeded,  so assignments to this variable have no effect.  If SRANDOM is unset, it
              loses its special properties, even if it is subsequently reset.
       UID    Expands to the user ID of the current user, initialized at shell startup.  This  variable  is
              readonly.

       The  following  variables  are  used by the shell.  In some cases, bash assigns a default value to a
       variable; these cases are noted below.

       BASH_COMPAT
              The value is used to set the shell's compatibility level.  See SHELL COMPATIBILITY MODE below
              for  a description of the various compatibility levels and their effects.  The value may be a
              decimal number (e.g., 4.2) or an integer (e.g., 42) corresponding to the desired  compatibil‐
              ity  level.   If  BASH_COMPAT is unset or set to the empty string, the compatibility level is
              set to the default for the current version.  If BASH_COMPAT is set to a value that is not one
              of the valid compatibility levels, the shell prints an error message and sets the compatibil‐
              ity level to the default for the current version.  The valid values correspond to the compat‐
              ibility  levels  described below under SHELL COMPATIBILITY MODE.  For example, 4.2 and 42 are
              valid values that correspond to the compat42 shopt option and set the compatibility level  to
              42.  The current version is also a valid value.
       BASH_ENV
              If this parameter is set when bash is executing a shell script, its value is interpreted as a
              filename containing commands to initialize the shell, as in ~/.bashrc.  The value of BASH_ENV
              is  subjected  to  parameter expansion, command substitution, and arithmetic expansion before
              being interpreted as a filename.  PATH is not used to search for the resultant filename.
       BASH_XTRACEFD
              If set to an integer corresponding to a valid file descriptor, bash will write the trace out‐
              put  generated when set -x is enabled to that file descriptor.  The file descriptor is closed
              when BASH_XTRACEFD is unset or assigned a new value.  Unsetting BASH_XTRACEFD or assigning it
              the empty string causes the trace output to be sent to the standard error.  Note that setting
              BASH_XTRACEFD to 2 (the standard error file descriptor) and then unsetting it will result  in
              the standard error being closed.
       CDPATH The  search  path for the cd command.  This is a colon-separated list of directories in which
              the shell looks for destination directories specified by the cd command.  A sample  value  is
              ".:~:/usr".
       CHILD_MAX
              Set  the number of exited child status values for the shell to remember.  Bash will not allow
              this value to be decreased below a POSIX-mandated minimum, and there is a maximum value (cur‐
              rently 8192) that this may not exceed.  The minimum value is system-dependent.
       COLUMNS
              Used  by  the select compound command to determine the terminal width when printing selection
              lists.  Automatically set if the checkwinsize option is enabled or in  an  interactive  shell
              upon receipt of a SIGWINCH.
       COMPREPLY
              An  array  variable from which bash reads the possible completions generated by a shell func‐
              tion invoked by the programmable completion facility  (see  Programmable  Completion  below).
              Each array element contains one possible completion.
       EMACS  If  bash  finds this variable in the environment when the shell starts with value "t", it as‐
              sumes that the shell is running in an Emacs shell buffer and disables line editing.
       ENV    Expanded and executed similarly to BASH_ENV (see INVOCATION above) when an interactive  shell
              is invoked in posix mode.
       EXECIGNORE
              A  colon-separated  list  of shell patterns (see Pattern Matching) defining the list of file‐
              names to be ignored by command search using PATH.  Files whose full pathnames  match  one  of
              these patterns are not considered executable files for the purposes of completion and command
              execution via PATH lookup.  This does not affect the behavior of the [,  test,  and  [[  com‐
              mands.   Full  pathnames  in  the command hash table are not subject to EXECIGNORE.  Use this
              variable to ignore shared library files that have the executable bit set, but  are  not  exe‐
              cutable files.  The pattern matching honors the setting of the extglob shell option.
       FCEDIT The default editor for the fc builtin command.
       FIGNORE
              A  colon-separated  list of suffixes to ignore when performing filename completion (see READ‐
              LINE below).  A filename whose suffix matches one of the entries in FIGNORE is excluded  from
              the  list of matched filenames.  A sample value is ".o:~" (Quoting is needed when assigning a
              value to this variable, which contains tildes).
       FUNCNEST
              If set to a numeric value greater than 0, defines a maximum function nesting level.  Function
              invocations that exceed this nesting level will cause the current command to abort.
       GLOBIGNORE
              A  colon-separated  list of patterns defining the set of file names to be ignored by pathname
              expansion.  If a file name matched by a pathname expansion pattern also matches  one  of  the
              patterns in GLOBIGNORE, it is removed from the list of matches.
       HISTCONTROL
              A  colon-separated list of values controlling how commands are saved on the history list.  If
              the list of values includes ignorespace, lines which begin with a  space  character  are  not
              saved  in the history list.  A value of ignoredups causes lines matching the previous history
              entry to not be saved.  A value of ignoreboth is shorthand for ignorespace and ignoredups.  A
              value of erasedups causes all previous lines matching the current line to be removed from the
              history list before that line is saved.  Any value not in the  above  list  is  ignored.   If
              HISTCONTROL  is  unset, or does not include a valid value, all lines read by the shell parser
              are saved on the history list, subject to the value of HISTIGNORE.  The second and subsequent
              lines  of  a multi-line compound command are not tested, and are added to the history regard‐
              less of the value of HISTCONTROL.
       HISTFILE
              The name of the file in which command history is saved  (see  HISTORY  below).   The  default
              value is ~/.bash_history.  If unset, the command history is not saved when a shell exits.
       HISTFILESIZE
              The  maximum number of lines contained in the history file.  When this variable is assigned a
              value, the history file is truncated, if necessary, to contain no more than  that  number  of
              lines  by removing the oldest entries.  The history file is also truncated to this size after
              writing it when a shell exits.  If the value is 0, the history  file  is  truncated  to  zero
              size.   Non-numeric  values  and numeric values less than zero inhibit truncation.  The shell
              sets the default value to the value of HISTSIZE after reading any startup files.
       HISTIGNORE
              A colon-separated list of patterns used to decide which command lines should be saved on  the
              history  list.  Each pattern is anchored at the beginning of the line and must match the com‐
              plete line (no implicit `*' is appended).  Each pattern is tested against the line after  the
              checks  specified by HISTCONTROL are applied.  In addition to the normal shell pattern match‐
              ing characters, `&' matches the previous history line.  `&' may be escaped using a backslash;
              the  backslash  is  removed  before attempting a match.  The second and subsequent lines of a
              multi-line compound command are not tested, and are added to the history  regardless  of  the
              value of HISTIGNORE.  The pattern matching honors the setting of the extglob shell option.
       HISTSIZE
              The  number of commands to remember in the command history (see HISTORY below).  If the value
              is 0, commands are not saved in the history list.  Numeric values less than  zero  result  in
              every  command  being  saved on the history list (there is no limit).  The shell sets the de‐
              fault value to 500 after reading any startup files.
       HISTTIMEFORMAT
              If this variable is set and not null, its value is used as a format string for strftime(3) to
              print the time stamp associated with each history entry displayed by the history builtin.  If
              this variable is set, time stamps are written to the history file so they  may  be  preserved
              across  shell  sessions.   This  uses the history comment character to distinguish timestamps
              from other history lines.
       HOME   The home directory of the current user; the default argument for the cd builtin command.  The
              value of this variable is also used when performing tilde expansion.
       HOSTFILE
              Contains  the  name  of  a file in the same format as /etc/hosts that should be read when the
              shell needs to complete a hostname.  The list of possible hostname completions may be changed
              while the shell is running; the next time hostname completion is attempted after the value is
              changed, bash adds the contents of the new file to the existing list.  If  HOSTFILE  is  set,
              but  has  no value, or does not name a readable file, bash attempts to read /etc/hosts to ob‐
              tain the list of possible hostname completions.  When HOSTFILE is unset, the hostname list is
              cleared.
       IFS    The  Internal  Field  Separator  that is used for word splitting after expansion and to split
              lines into words with the read builtin command.  The  default  value  is  ``<space><tab><new‐
              line>''.
       IGNOREEOF
              Controls the action of an interactive shell on receipt of an EOF character as the sole input.
              If set, the value is the number of consecutive EOF characters which  must  be  typed  as  the
              first  characters  on  an  input line before bash exits.  If the variable exists but does not
              have a numeric value, or has no value, the default value is 10.  If it does  not  exist,  EOF
              signifies the end of input to the shell.
       INPUTRC
              The  filename  for the readline startup file, overriding the default of ~/.inputrc (see READ‐
              LINE below).
       INSIDE_EMACS
              If this variable appears in the environment when the shell starts, bash assumes  that  it  is
              running  inside an Emacs shell buffer and may disable line editing, depending on the value of
              TERM.
       LANG   Used to determine the locale category for any category not specifically selected with a vari‐
              able starting with LC_.
       LC_ALL This variable overrides the value of LANG and any other LC_ variable specifying a locale cat‐
              egory.
       LC_COLLATE
              This variable determines the collation order used when sorting the results of pathname expan‐
              sion,  and  determines  the behavior of range expressions, equivalence classes, and collating
              sequences within pathname expansion and pattern matching.
       LC_CTYPE
              This variable determines the interpretation of  characters  and  the  behavior  of  character
              classes within pathname expansion and pattern matching.
       LC_MESSAGES
              This variable determines the locale used to translate double-quoted strings preceded by a $.
       LC_NUMERIC
              This variable determines the locale category used for number formatting.
       LC_TIME
              This variable determines the locale category used for data and time formatting.
       LINES  Used  by  the  select  compound command to determine the column length for printing selection
              lists.  Automatically set if the checkwinsize option is enabled or in  an  interactive  shell
              upon receipt of a SIGWINCH.
       MAIL   If  this  parameter  is set to a file or directory name and the MAILPATH variable is not set,
              bash informs the user of the arrival of mail in the specified file or  Maildir-format  direc‐
              tory.
       MAILCHECK
              Specifies  how  often (in seconds) bash checks for mail.  The default is 60 seconds.  When it
              is time to check for mail, the shell does so before displaying the primary prompt.   If  this
              variable  is unset, or set to a value that is not a number greater than or equal to zero, the
              shell disables mail checking.
       MAILPATH
              A colon-separated list of filenames to be checked for mail.  The message to be  printed  when
              mail  arrives  in a particular file may be specified by separating the filename from the mes‐
              sage with a `?'.  When used in the text of the message, $_ expands to the name of the current
              mailfile.  Example:
              MAILPATH='/var/mail/bfox?"You have mail":~/shell-mail?"$_ has mail!"'
              Bash  can be configured to supply a default value for this variable (there is no value by de‐
              fault), but the location of the user mail files that  it  uses  is  system  dependent  (e.g.,
              /var/mail/$USER).
       OPTERR If  set to the value 1, bash displays error messages generated by the getopts builtin command
              (see SHELL BUILTIN COMMANDS below).  OPTERR is initialized to 1 each time the  shell  is  in‐
              voked or a shell script is executed.
       PATH   The search path for commands.  It is a colon-separated list of directories in which the shell
              looks for commands (see COMMAND EXECUTION below).  A zero-length (null) directory name in the
              value of PATH indicates the current directory.  A null directory name may appear as two adja‐
              cent colons, or as an initial or trailing colon.  The default path is  system-dependent,  and
              is set by the administrator who installs bash.  A common value is ``/usr/local/bin:/usr/lo‐
              cal/sbin:/usr/bin:/usr/sbin:/bin:/sbin''.
       POSIXLY_CORRECT
              If this variable is in the environment when bash starts, the shell enters posix  mode  before
              reading  the  startup files, as if the --posix invocation option had been supplied.  If it is
              set while the shell is running, bash enables posix mode, as if the command set -o  posix  had
              been executed.  When the shell enters posix mode, it sets this variable if it was not already
              set.
       PROMPT_COMMAND
              If this variable is set, and is an array, the value of each set element is executed as a com‐
              mand  prior  to  issuing  each primary prompt.  If this is set but not an array variable, its
              value is used as a command to execute instead.
       PROMPT_DIRTRIM
              If set to a number greater than zero, the value is used as the number of  trailing  directory
              components  to  retain  when expanding the \w and \W prompt string escapes (see PROMPTING be‐
              low).  Characters removed are replaced with an ellipsis.
       PS0    The value of this parameter is expanded (see PROMPTING below) and  displayed  by  interactive
              shells after reading a command and before the command is executed.
       PS1    The  value of this parameter is expanded (see PROMPTING below) and used as the primary prompt
              string.  The default value is ``\s-\v\$ ''.
       PS2    The value of this parameter is expanded as with PS1 and used as the secondary prompt  string.
              The default is ``> ''.
       PS3    The  value  of this parameter is used as the prompt for the select command (see SHELL GRAMMAR
              above).
       PS4    The value of this parameter is expanded as with PS1 and the value is printed before each com‐
              mand  bash  displays during an execution trace.  The first character of the expanded value of
              PS4 is replicated multiple times, as necessary, to indicate multiple levels  of  indirection.
              The default is ``+ ''.
       SHELL  This  variable  expands  to  the full pathname to the shell.  If it is not set when the shell
              starts, bash assigns to it the full pathname of the current user's login shell.
       TIMEFORMAT
              The value of this parameter is used as a format string specifying how the timing  information
              for  pipelines prefixed with the time reserved word should be displayed.  The % character in‐
              troduces an escape sequence that is expanded to a time value or other information.   The  es‐
              cape sequences and their meanings are as follows; the braces denote optional portions.
              %%        A literal %.
              %[p][l]R  The elapsed time in seconds.
              %[p][l]U  The number of CPU seconds spent in user mode.
              %[p][l]S  The number of CPU seconds spent in system mode.
              %P        The CPU percentage, computed as (%U + %S) / %R.

              The  optional  p is a digit specifying the precision, the number of fractional digits after a
              decimal point.  A value of 0 causes no decimal point or fraction to be output.  At most three
              places after the decimal point may be specified; values of p greater than 3 are changed to 3.
              If p is not specified, the value 3 is used.

              The optional l specifies a longer format, including minutes,  of  the  form  MMmSS.FFs.   The
              value of p determines whether or not the fraction is included.

              If    this    variable    is    not    set,    bash   acts   as   if   it   had   the   value
              $'\nreal\t%3lR\nuser\t%3lU\nsys\t%3lS'.  If the value is null, no timing information is  dis‐
              played.  A trailing newline is added when the format string is displayed.
       TMOUT  If  set  to  a  value greater than zero, TMOUT is treated as the default timeout for the read
              builtin.  The select command terminates if input does not arrive after TMOUT seconds when in‐
              put is coming from a terminal.  In an interactive shell, the value is interpreted as the num‐
              ber of seconds to wait for a line of input after issuing the primary prompt.  Bash terminates
              after waiting for that number of seconds if a complete line of input does not arrive.
       TMPDIR If  set, bash uses its value as the name of a directory in which bash creates temporary files
              for the shell's use.
       auto_resume
              This variable controls how the shell interacts with the user and job control.  If this  vari‐
              able  is  set, single word simple commands without redirections are treated as candidates for
              resumption of an existing stopped job.  There is no ambiguity allowed; if there is more  than
              one  job  beginning  with  the string typed, the job most recently accessed is selected.  The
              name of a stopped job, in this context, is the command line used to start it.  If set to  the
              value exact, the string supplied must match the name of a stopped job exactly; if set to sub‐
              string, the string supplied needs to match a substring of the name of  a  stopped  job.   The
              substring  value  provides functionality analogous to the %?  job identifier (see JOB CONTROL
              below).  If set to any other value, the supplied string must be a prefix of a  stopped  job's
              name; this provides functionality analogous to the %string job identifier.
       histchars
              The two or three characters which control history expansion and tokenization (see HISTORY EX‐
              PANSION below).  The first character is the history expansion character, the character  which
              signals  the  start  of a history expansion, normally `!'.  The second character is the quick
              substitution character, which is used as shorthand for re-running the  previous  command  en‐
              tered, substituting one string for another in the command.  The default is `^'.  The optional
              third character is the character which indicates that the remainder of the line is a  comment
              when  found  as  the  first character of a word, normally `#'.  The history comment character
              causes history substitution to be skipped for the remaining words on the line.  It  does  not
              necessarily cause the shell parser to treat the rest of the line as a comment.

   Arrays
       Bash  provides one-dimensional indexed and associative array variables.  Any variable may be used as
       an indexed array; the declare builtin will explicitly declare an array.  There is no  maximum  limit
       on  the size of an array, nor any requirement that members be indexed or assigned contiguously.  In‐
       dexed arrays are referenced using integers (including arithmetic expressions)  and  are  zero-based;
       associative  arrays  are  referenced using arbitrary strings.  Unless otherwise noted, indexed array
       indices must be non-negative integers.

       An indexed array is created automatically if any variable is assigned to using the syntax  name[sub‐
       script]=value.  The subscript is treated as an arithmetic expression that must evaluate to a number.
       To explicitly declare an indexed array, use declare -a name (see SHELL BUILTIN COMMANDS below).  de‐
       clare -a name[subscript] is also accepted; the subscript is ignored.

       Associative arrays are created using declare -A name.

       Attributes may be specified for an array variable using the declare and readonly builtins.  Each at‐
       tribute applies to all members of an array.

       Arrays are assigned to using compound assignments of the form name=(value1 ... valuen),  where  each
       value  may be of the form [subscript]=string.  Indexed array assignments do not require anything but
       string.  Each value in the list is expanded using all the shell expansions described below under EX‐
       PANSION.   When  assigning  to  indexed arrays, if the optional brackets and subscript are supplied,
       that index is assigned to; otherwise the index of the element assigned is the last index assigned to
       by the statement plus one.  Indexing starts at zero.

       When  assigning to an associative array, the words in a compound assignment may be either assignment
       statements, for which the subscript is required, or a list of words that is  interpreted  as  a  se‐
       quence of alternating keys and values: name=( key1 value1 key2 value2 ...).  These are treated iden‐
       tically to name=( [key1]=value1 [key2]=value2 ...).  The first word in the list determines  how  the
       remaining  words  are  interpreted;  all assignments in a list must be of the same type.  When using
       key/value pairs, the keys may not be missing or empty; a final missing value  is  treated  like  the
       empty string.

       This  syntax  is also accepted by the declare builtin.  Individual array elements may be assigned to
       using the name[subscript]=value syntax introduced above.  When assigning to  an  indexed  array,  if
       name is subscripted by a negative number, that number is interpreted as relative to one greater than
       the maximum index of name, so negative indices count back from the end of the array, and an index of
       -1 references the last element.

       The  +=  operator will append to an array variable when assigning using the compound assignment syn‐
       tax; see PARAMETERS above.

       Any element of an array may be referenced using ${name[subscript]}.   The  braces  are  required  to
       avoid conflicts with pathname expansion.  If subscript is @ or *, the word expands to all members of
       name.  These subscripts differ only when the word appears within double quotes.  If the word is dou‐
       ble-quoted, ${name[*]} expands to a single word with the value of each array member separated by the
       first character of the IFS special variable, and ${name[@]} expands each element of name to a  sepa‐
       rate  word.   When  there are no array members, ${name[@]} expands to nothing.  If the double-quoted
       expansion occurs within a word, the expansion of the first parameter is joined  with  the  beginning
       part  of  the original word, and the expansion of the last parameter is joined with the last part of
       the original word.  This is analogous to the expansion of the special parameters * and @  (see  Spe‐
       cial  Parameters  above).  ${#name[subscript]} expands to the length of ${name[subscript]}.  If sub‐
       script is * or @, the expansion is the number of elements in the array.  If the  subscript  used  to
       reference  an element of an indexed array evaluates to a number less than zero, it is interpreted as
       relative to one greater than the maximum index of the array, so negative indices count back from the
       end of the array, and an index of -1 references the last element.

       Referencing an array variable without a subscript is equivalent to referencing the array with a sub‐
       script of 0.  Any reference to a variable using a valid subscript is legal, and bash will create  an
       array if necessary.

       An  array variable is considered set if a subscript has been assigned a value.  The null string is a
       valid value.

       It is possible to obtain the keys (indices) of an array as well  as  the  values.   ${!name[@]}  and
       ${!name[*]}  expand  to  the  indices assigned in array variable name.  The treatment when in double
       quotes is similar to the expansion of the special parameters @ and * within double quotes.

       The unset builtin is used to destroy arrays.  unset name[subscript] destroys the  array  element  at
       index subscript, for both indexed and associative arrays.  Negative subscripts to indexed arrays are
       interpreted as described above.  Unsetting the last element of an array variable does not unset  the
       variable.   unset  name,  where  name is an array, removes the entire array.  unset name[subscript],
       where subscript is * or @, behaves differently depending on whether name is an indexed  or  associa‐
       tive  array.   If  name  is an associative array, this unsets the element with subscript * or @.  If
       name is an indexed array, unset removes all of the elements but does not remove the array itself.

       When using a variable name with a subscript as an argument to a command, such as with unset, without
       using  the word expansion syntax described above, the argument is subject to pathname expansion.  If
       pathname expansion is not desired, the argument should be quoted.

       The declare, local, and readonly builtins each accept a -a option to specify an indexed array and  a
       -A  option to specify an associative array.  If both options are supplied, -A takes precedence.  The
       read builtin accepts a -a option to assign a list of words read from the standard input to an array.
       The  set and declare builtins display array values in a way that allows them to be reused as assign‐
       ments.

EXPANSION
       Expansion is performed on the command line after it has been split  into  words.   There  are  seven
       kinds  of  expansion  performed: brace expansion, tilde expansion, parameter and variable expansion,
       command substitution, arithmetic expansion, word splitting, and pathname expansion.

       The order of expansions is: brace expansion; tilde  expansion,  parameter  and  variable  expansion,
       arithmetic  expansion,  and  command substitution (done in a left-to-right fashion); word splitting;
       and pathname expansion.

       On systems that can support it, there is an additional expansion  available:  process  substitution.
       This  is performed at the same time as tilde, parameter, variable, and arithmetic expansion and com‐
       mand substitution.

       After these expansions are performed, quote characters present in the original word are removed  un‐
       less they have been quoted themselves (quote removal).

       Only brace expansion, word splitting, and pathname expansion can increase the number of words of the
       expansion; other expansions expand a single word to a single word.  The only exceptions to this  are
       the  expansions  of  "$@" and "${name[@]}", and, in most cases, $* and ${name[*]} as explained above
       (see PARAMETERS).

   Brace Expansion
       Brace expansion is a mechanism by which arbitrary strings may be generated.  This mechanism is simi‐
       lar  to  pathname  expansion,  but the filenames generated need not exist.  Patterns to be brace ex‐
       panded take the form of an optional preamble, followed by either a series of comma-separated strings
       or a sequence expression between a pair of braces, followed by an optional postscript.  The preamble
       is prefixed to each string contained within the braces, and the postscript is then appended to  each
       resulting string, expanding left to right.

       Brace  expansions  may be nested.  The results of each expanded string are not sorted; left to right
       order is preserved.  For example, a{d,c,b}e expands into `ade ace abe'.

       A sequence expression takes the form {x..y[..incr]}, where x and y are  either  integers  or  single
       letters, and incr, an optional increment, is an integer.  When integers are supplied, the expression
       expands to each number between x and y, inclusive.  Supplied integers may  be  prefixed  with  0  to
       force  each  term to have the same width.  When either x or y begins with a zero, the shell attempts
       to force all generated terms to contain the same number of  digits,  zero-padding  where  necessary.
       When  letters are supplied, the expression expands to each character lexicographically between x and
       y, inclusive, using the default C locale.  Note that both x and y must be of the same type  (integer
       or  letter).   When  the increment is supplied, it is used as the difference between each term.  The
       default increment is 1 or -1 as appropriate.

       Brace expansion is performed before any other expansions, and any characters special to other expan‐
       sions  are  preserved in the result.  It is strictly textual.  Bash does not apply any syntactic in‐
       terpretation to the context of the expansion or the text between the braces.

       A correctly-formed brace expansion must contain unquoted opening and closing braces,  and  at  least
       one  unquoted  comma or a valid sequence expression.  Any incorrectly formed brace expansion is left
       unchanged.  A { or , may be quoted with a backslash to prevent its being considered part of a  brace
       expression.   To  avoid conflicts with parameter expansion, the string ${ is not considered eligible
       for brace expansion, and inhibits brace expansion until the closing }.

       This construct is typically used as shorthand when the common prefix of the strings to be  generated
       is longer than in the above example:

              mkdir /usr/local/src/bash/{old,new,dist,bugs}
       or
              chown root /usr/{ucb/{ex,edit},lib/{ex?.?*,how_ex}}

       Brace  expansion  introduces  a  slight incompatibility with historical versions of sh.  sh does not
       treat opening or closing braces specially when they appear as part of a word, and preserves them  in
       the  output.   Bash  removes  braces from words as a consequence of brace expansion.  For example, a
       word entered to sh as file{1,2} appears identically in the output.  The same word is output as file1
       file2  after  expansion by bash.  If strict compatibility with sh is desired, start bash with the +B
       option or disable brace expansion with the +B option to the set command (see SHELL BUILTIN  COMMANDS
       below).

   Tilde Expansion
       If  a  word begins with an unquoted tilde character (`~'), all of the characters preceding the first
       unquoted slash (or all characters, if there is no unquoted slash) are considered a tilde-prefix.  If
       none  of the characters in the tilde-prefix are quoted, the characters in the tilde-prefix following
       the tilde are treated as a possible login name.  If this login name is the null string, the tilde is
       replaced  with  the  value of the shell parameter HOME.  If HOME is unset, the home directory of the
       user executing the shell is substituted instead.  Otherwise, the tilde-prefix is replaced  with  the
       home directory associated with the specified login name.

       If  the  tilde-prefix  is a `~+', the value of the shell variable PWD replaces the tilde-prefix.  If
       the tilde-prefix is a `~-', the value of the shell variable OLDPWD, if it is  set,  is  substituted.
       If the characters following the tilde in the tilde-prefix consist of a number N, optionally prefixed
       by a `+' or a `-', the tilde-prefix is replaced with the corresponding element  from  the  directory
       stack,  as  it  would be displayed by the dirs builtin invoked with the tilde-prefix as an argument.
       If the characters following the tilde in the tilde-prefix consist of a number without a leading  `+'
       or `-', `+' is assumed.

       If the login name is invalid, or the tilde expansion fails, the word is unchanged.

       Each  variable  assignment  is  checked for unquoted tilde-prefixes immediately following a : or the
       first =.  In these cases, tilde expansion is also performed.  Consequently, one  may  use  filenames
       with tildes in assignments to PATH, MAILPATH, and CDPATH, and the shell assigns the expanded value.

       Bash  also  performs  tilde expansion on words satisfying the conditions of variable assignments (as
       described above under PARAMETERS) when they appear as arguments to simple commands.  Bash  does  not
       do this, except for the declaration commands listed above, when in posix mode.

   Parameter Expansion
       The  `$'  character  introduces  parameter expansion, command substitution, or arithmetic expansion.
       The parameter name or symbol to be expanded may be enclosed in braces, which are optional but  serve
       to  protect  the variable to be expanded from characters immediately following it which could be in‐
       terpreted as part of the name.

       When braces are used, the matching ending brace is the first `}'  not  escaped  by  a  backslash  or
       within  a  quoted  string, and not within an embedded arithmetic expansion, command substitution, or
       parameter expansion.

       ${parameter}
              The value of parameter is substituted.  The braces are required when  parameter  is  a  posi‐
              tional parameter with more than one digit, or when parameter is followed by a character which
              is not to be interpreted as part of its name.  The parameter is  a  shell  parameter  as  de‐
              scribed above PARAMETERS) or an array reference (Arrays).

       If  the first character of parameter is an exclamation point (!), and parameter is not a nameref, it
       introduces a level of indirection.  Bash uses the value formed by expanding the rest of parameter as
       the new parameter; this is then expanded and that value is used in the rest of the expansion, rather
       than the expansion of the original parameter.  This is known as indirect expansion.   The  value  is
       subject to tilde expansion, parameter expansion, command substitution, and arithmetic expansion.  If
       parameter is a nameref, this expands to the name of the parameter referenced by parameter instead of
       performing  the  complete  indirect expansion.  The exceptions to this are the expansions of ${!pre‐
       fix*} and ${!name[@]} described below.  The exclamation point must immediately follow the left brace
       in order to introduce indirection.

       In each of the cases below, word is subject to tilde expansion, parameter expansion, command substi‐
       tution, and arithmetic expansion.

       When not performing substring expansion, using the forms documented below (e.g., :-), bash tests for
       a  parameter  that is unset or null.  Omitting the colon results in a test only for a parameter that
       is unset.

       ${parameter:-word}
              Use Default Values.  If parameter is unset or null, the expansion  of  word  is  substituted.
              Otherwise, the value of parameter is substituted.
       ${parameter:=word}
              Assign  Default  Values.  If parameter is unset or null, the expansion of word is assigned to
              parameter.  The value of parameter is then substituted.  Positional  parameters  and  special
              parameters may not be assigned to in this way.
       ${parameter:?word}
              Display  Error  if Null or Unset.  If parameter is null or unset, the expansion of word (or a
              message to that effect if word is not present) is written  to  the  standard  error  and  the
              shell, if it is not interactive, exits.  Otherwise, the value of parameter is substituted.
       ${parameter:+word}
              Use  Alternate  Value.   If parameter is null or unset, nothing is substituted, otherwise the
              expansion of word is substituted.
       ${parameter:offset}
       ${parameter:offset:length}
              Substring Expansion.  Expands to up to length characters of the value of  parameter  starting
              at  the  character specified by offset.  If parameter is @ or *, an indexed array subscripted
              by @ or *, or an associative array name, the results differ as described below.  If length is
              omitted,  expands to the substring of the value of parameter starting at the character speci‐
              fied by offset and extending to the end of the value.  length and offset are  arithmetic  ex‐
              pressions (see ARITHMETIC EVALUATION below).

              If  offset evaluates to a number less than zero, the value is used as an offset in characters
              from the end of the value of parameter.  If length evaluates to a number less than  zero,  it
              is  interpreted as an offset in characters from the end of the value of parameter rather than
              a number of characters, and the expansion is the characters between offset and  that  result.
              Note  that  a negative offset must be separated from the colon by at least one space to avoid
              being confused with the :- expansion.

              If parameter is @ or *, the result is length positional parameters beginning  at  offset.   A
              negative  offset  is taken relative to one greater than the greatest positional parameter, so
              an offset of -1 evaluates to the last positional parameter.  It  is  an  expansion  error  if
              length evaluates to a number less than zero.

              If parameter is an indexed array name subscripted by @ or *, the result is the length members
              of the array beginning with ${parameter[offset]}.  A negative offset is taken relative to one
              greater  than  the  maximum index of the specified array.  It is an expansion error if length
              evaluates to a number less than zero.

              Substring expansion applied to an associative array produces undefined results.

              Substring indexing is zero-based unless the positional parameters are used, in which case the
              indexing  starts at 1 by default.  If offset is 0, and the positional parameters are used, $0
              is prefixed to the list.

       ${!prefix*}
       ${!prefix@}
              Names matching prefix.  Expands to the names of variables whose names begin with prefix, sep‐
              arated  by the first character of the IFS special variable.  When @ is used and the expansion
              appears within double quotes, each variable name expands to a separate word.

       ${!name[@]}
       ${!name[*]}
              List of array keys.  If name is an array variable, expands  to  the  list  of  array  indices
              (keys)  assigned in name.  If name is not an array, expands to 0 if name is set and null oth‐
              erwise.  When @ is used and the expansion appears within double quotes, each key expands to a
              separate word.

       ${#parameter}
              Parameter length.  The length in characters of the value of parameter is substituted.  If pa‐
              rameter is * or @, the value substituted is the number of positional parameters.  If  parame‐
              ter  is  an array name subscripted by * or @, the value substituted is the number of elements
              in the array.  If parameter is an indexed array name subscripted by a negative  number,  that
              number is interpreted as relative to one greater than the maximum index of parameter, so neg‐
              ative indices count back from the end of the array, and an index of -1  references  the  last
              element.

       ${parameter#word}
       ${parameter##word}
              Remove  matching  prefix pattern.  The word is expanded to produce a pattern just as in path‐
              name expansion, and matched against the expanded value of parameter using the rules described
              under  Pattern  Matching below.  If the pattern matches the beginning of the value of parame‐
              ter, then the result of the expansion is the expanded value of parameter  with  the  shortest
              matching  pattern (the ``#'' case) or the longest matching pattern (the ``##'' case) deleted.
              If parameter is @ or *, the pattern removal operation is applied to each positional parameter
              in  turn,  and  the  expansion is the resultant list.  If parameter is an array variable sub‐
              scripted with @ or *, the pattern removal operation is applied to each member of the array in
              turn, and the expansion is the resultant list.

       ${parameter%word}
       ${parameter%%word}
              Remove  matching  suffix pattern.  The word is expanded to produce a pattern just as in path‐
              name expansion, and matched against the expanded value of parameter using the rules described
              under  Pattern  Matching  below.   If  the pattern matches a trailing portion of the expanded
              value of parameter, then the result of the expansion is the expanded value of parameter  with
              the  shortest  matching  pattern (the ``%'' case) or the longest matching pattern (the ``%%''
              case) deleted.  If parameter is @ or *, the pattern removal operation is applied to each  po‐
              sitional  parameter in turn, and the expansion is the resultant list.  If parameter is an ar‐
              ray variable subscripted with @ or *, the pattern removal operation is applied to each member
              of the array in turn, and the expansion is the resultant list.

       ${parameter/pattern/string}
       ${parameter//pattern/string}
       ${parameter/#pattern/string}
       ${parameter/%pattern/string}
              Pattern  substitution.   The pattern is expanded to produce a pattern just as in pathname ex‐
              pansion.  Parameter is expanded and the longest match of pattern against  its  value  is  re‐
              placed  with  string.   string  undergoes  tilde expansion, parameter and variable expansion,
              arithmetic expansion, command and process substitution, and quote removal.  The match is per‐
              formed using the rules described under Pattern Matching below.  In the first form above, only
              the first match is replaced.  If there are two slashes separating parameter and pattern  (the
              second  form above), all matches of pattern are replaced with string.  If pattern is preceded
              by # (the third form above), it must match at the beginning of the expanded value of  parame‐
              ter.   If  pattern  is preceded by % (the fourth form above), it must match at the end of the
              expanded value of parameter.  If the expansion of string is  null,  matches  of  pattern  are
              deleted.   If  string is null, matches of pattern are deleted and the / following pattern may
              be omitted.

              If the patsub_replacement shell option is enabled using shopt, any unquoted instances of & in
              string are replaced with the matching portion of pattern.

              Quoting  any  part of string inhibits replacement in the expansion of the quoted portion, in‐
              cluding replacement strings stored in shell variables.  Backslash will escape  &  in  string;
              the backslash is removed in order to permit a literal & in the replacement string.  Backslash
              can also be used to escape a backslash; \\ results in a literal backslash in the replacement.
              Users  should take care if string is double-quoted to avoid unwanted interactions between the
              backslash and double-quoting, since backslash has special meaning within double quotes.  Pat‐
              tern substitution performs the check for unquoted & after expanding string; shell programmers
              should quote any occurrences of & they want to be taken literally in the replacement and  en‐
              sure any instances of & they want to be replaced are unquoted.

              If the nocasematch shell option is enabled, the match is performed without regard to the case
              of alphabetic characters.  If parameter is @ or *, the substitution operation is  applied  to
              each  positional parameter in turn, and the expansion is the resultant list.  If parameter is
              an array variable subscripted with @ or *, the substitution operation is applied to each mem‐
              ber of the array in turn, and the expansion is the resultant list.

       ${parameter^pattern}
       ${parameter^^pattern}
       ${parameter,pattern}
       ${parameter,,pattern}
              Case  modification.   This expansion modifies the case of alphabetic characters in parameter.
              The pattern is expanded to produce a pattern just as in pathname expansion.   Each  character
              in the expanded value of parameter is tested against pattern, and, if it matches the pattern,
              its case is converted.  The pattern should not attempt to match more than one character.  The
              ^  operator converts lowercase letters matching pattern to uppercase; the , operator converts
              matching uppercase letters to lowercase.  The ^^ and ,, expansions convert each matched char‐
              acter  in the expanded value; the ^ and , expansions match and convert only the first charac‐
              ter in the expanded value.  If pattern is omitted, it is treated like a ?, which matches  ev‐
              ery  character.   If  parameter is @ or *, the case modification operation is applied to each
              positional parameter in turn, and the expansion is the resultant list.  If  parameter  is  an
              array  variable  subscripted  with @ or *, the case modification operation is applied to each
              member of the array in turn, and the expansion is the resultant list.

       ${parameter@operator}
              Parameter transformation.  The expansion is either a transformation of the value of parameter
              or  information about parameter itself, depending on the value of operator.  Each operator is
              a single letter:

              U      The expansion is a string that is the value of  parameter  with  lowercase  alphabetic
                     characters converted to uppercase.
              u      The expansion is a string that is the value of parameter with the first character con‐
                     verted to uppercase, if it is alphabetic.
              L      The expansion is a string that is the value of  parameter  with  uppercase  alphabetic
                     characters converted to lowercase.
              Q      The  expansion  is a string that is the value of parameter quoted in a format that can
                     be reused as input.
              E      The expansion is a string that is the value of parameter  with  backslash  escape  se‐
                     quences expanded as with the $'...' quoting mechanism.
              P      The expansion is a string that is the result of expanding the value of parameter as if
                     it were a prompt string (see PROMPTING below).
              A      The expansion is a string in the form of an assignment statement  or  declare  command
                     that, if evaluated, will recreate parameter with its attributes and value.
              K      Produces  a  possibly-quoted  version of the value of parameter, except that it prints
                     the values of indexed and associative arrays as a sequence of quoted  key-value  pairs
                     (see Arrays above).
              a      The  expansion  is  a  string  consisting  of flag values representing parameter's at‐
                     tributes.
              k      Like the K transformation, but expands the keys and values of indexed and  associative
                     arrays to separate words after word splitting.

              If  parameter  is  @ or *, the operation is applied to each positional parameter in turn, and
              the expansion is the resultant list.  If parameter is an array variable subscripted with @ or
              *, the operation is applied to each member of the array in turn, and the expansion is the re‐
              sultant list.

              The result of the expansion is subject to word splitting and pathname expansion as  described
              below.

   Command Substitution
       Command  substitution  allows  the  output  of a command to replace the command name.  There are two
       forms:

              $(command)
       or
              `command`

       Bash performs the expansion by executing command in a subshell environment and replacing the command
       substitution  with the standard output of the command, with any trailing newlines deleted.  Embedded
       newlines are not deleted, but they may be removed during word splitting.  The  command  substitution
       $(cat file) can be replaced by the equivalent but faster $(< file).

       When the old-style backquote form of substitution is used, backslash retains its literal meaning ex‐
       cept when followed by $, `, or \.  The first backquote not preceded by a  backslash  terminates  the
       command  substitution.   When using the $(command) form, all characters between the parentheses make
       up the command; none are treated specially.

       Command substitutions may be nested.  To nest when using the backquoted form, escape the inner back‐
       quotes with backslashes.

       If the substitution appears within double quotes, word splitting and pathname expansion are not per‐
       formed on the results.

   Arithmetic Expansion
       Arithmetic expansion allows the evaluation of an arithmetic expression and the substitution  of  the
       result.  The format for arithmetic expansion is:

              $((expression))

       The old format $[expression] is deprecated and will be removed in upcoming versions of bash.

       The  expression  undergoes  the same expansions as if it were within double quotes, but double quote
       characters in expression are not treated specially and are removed.  All tokens  in  the  expression
       undergo  parameter  and  variable expansion, command substitution, and quote removal.  The result is
       treated as the arithmetic expression to be evaluated.  Arithmetic expansions may be nested.

       The evaluation is performed according to the rules listed below under ARITHMETIC EVALUATION.  If ex‐
       pression is invalid, bash prints a message indicating failure and no substitution occurs.

   Process Substitution
       Process  substitution  allows  a  process's  input or output to be referred to using a filename.  It
       takes the form of <(list) or >(list).  The process list is run asynchronously, and its input or out‐
       put appears as a filename.  This filename is passed as an argument to the current command as the re‐
       sult of the expansion.  If the >(list) form is used, writing to the  file  will  provide  input  for
       list.  If the <(list) form is used, the file passed as an argument should be read to obtain the out‐
       put of list.  Process substitution is supported on systems that support named pipes (FIFOs)  or  the
       /dev/fd method of naming open files.

       When  available, process substitution is performed simultaneously with parameter and variable expan‐
       sion, command substitution, and arithmetic expansion.

   Word Splitting
       The shell scans the results of parameter expansion, command substitution, and  arithmetic  expansion
       that did not occur within double quotes for word splitting.

       The  shell  treats  each character of IFS as a delimiter, and splits the results of the other expan‐
       sions into words using these characters as field terminators.  If IFS is unset, or its value is  ex‐
       actly <space><tab><newline>, the default, then sequences of <space>, <tab>, and <newline> at the be‐
       ginning and end of the results of the previous expansions are ignored, and any sequence of IFS char‐
       acters  not  at the beginning or end serves to delimit words.  If IFS has a value other than the de‐
       fault, then sequences of the whitespace characters space, tab, and newline are ignored at the begin‐
       ning  and end of the word, as long as the whitespace character is in the value of IFS (an IFS white‐
       space character).  Any character in IFS that is not IFS whitespace,  along  with  any  adjacent  IFS
       whitespace characters, delimits a field.  A sequence of IFS whitespace characters is also treated as
       a delimiter.  If the value of IFS is null, no word splitting occurs.

       Explicit null arguments ("" or '') are retained and passed to commands as empty  strings.   Unquoted
       implicit  null  arguments,  resulting  from the expansion of parameters that have no values, are re‐
       moved.  If a parameter with no value is expanded within double quotes, a null argument  results  and
       is retained and passed to a command as an empty string.  When a quoted null argument appears as part
       of a word whose expansion is non-null, the null argument is removed.  That is, the word -d'' becomes
       -d after word splitting and null argument removal.

       Note that if no expansion occurs, no splitting is performed.

   Pathname Expansion
       After  word splitting, unless the -f option has been set, bash scans each word for the characters *,
       ?, and [.  If one of these characters appears, and is not quoted, then the word  is  regarded  as  a
       pattern, and replaced with an alphabetically sorted list of filenames matching the pattern (see Pat‐
       tern Matching below).  If no matching filenames are found, and the shell option nullglob is not  en‐
       abled,  the  word  is  left unchanged.  If the nullglob option is set, and no matches are found, the
       word is removed.  If the failglob shell option is set, and no matches are found, an error message is
       printed  and  the  command is not executed.  If the shell option nocaseglob is enabled, the match is
       performed without regard to the case of alphabetic characters.  Note that when using  range  expres‐
       sions like [a-z] (see below), letters of the other case may be included, depending on the setting of
       LC_COLLATE.  When a pattern is used for pathname expansion, the character ``.''  at the start  of  a
       name or immediately following a slash must be matched explicitly, unless the shell option dotglob is
       set.  In order to match the filenames ``.''  and ``..'', the pattern must begin with ``.'' (for  ex‐
       ample,  ``.?''), even if dotglob is set.  If the globskipdots shell option is enabled, the filenames
       ``.''  and ``..''  are never matched, even if the pattern begins with a ``.''.   When  not  matching
       pathnames, the ``.''  character is not treated specially.  When matching a pathname, the slash char‐
       acter must always be matched explicitly by a slash in the pattern, but in other matching contexts it
       can  be  matched  by a special pattern character as described below under Pattern Matching.  See the
       description of shopt below under SHELL BUILTIN COMMANDS for a description of the  nocaseglob,  null‐
       glob, globskipdots, failglob, and dotglob shell options.

       The  GLOBIGNORE shell variable may be used to restrict the set of file names matching a pattern.  If
       GLOBIGNORE is set, each matching file name that also matches one of the patterns  in  GLOBIGNORE  is
       removed  from  the  list of matches.  If the nocaseglob option is set, the matching against the pat‐
       terns in GLOBIGNORE is performed without regard to case.  The filenames ``.''  and ``..''   are  al‐
       ways  ignored  when GLOBIGNORE is set and not null.  However, setting GLOBIGNORE to a non-null value
       has the effect of enabling the dotglob shell option, so all other filenames beginning with  a  ``.''
       will  match.  To get the old behavior of ignoring filenames beginning with a ``.'', make ``.*''  one
       of the patterns in GLOBIGNORE.  The dotglob option is disabled when GLOBIGNORE is unset.   The  pat‐
       tern matching honors the setting of the extglob shell option.

       Pattern Matching

       Any  character that appears in a pattern, other than the special pattern characters described below,
       matches itself.  The NUL character may not occur in a pattern.  A backslash  escapes  the  following
       character;  the  escaping backslash is discarded when matching.  The special pattern characters must
       be quoted if they are to be matched literally.

       The special pattern characters have the following meanings:

              *      Matches any string, including the null string.  When the globstar shell option is  en‐
                     abled, and * is used in a pathname expansion context, two adjacent *s used as a single
                     pattern will match all files and zero or more directories and subdirectories.  If fol‐
                     lowed by a /, two adjacent *s will match only directories and subdirectories.
              ?      Matches any single character.
              [...]  Matches  any  one of the enclosed characters.  A pair of characters separated by a hy‐
                     phen denotes a range expression; any character that falls between  those  two  charac‐
                     ters,  inclusive,  using the current locale's collating sequence and character set, is
                     matched.  If the first character following the [ is a !  or a ^ then any character not
                     enclosed  is  matched.   The sorting order of characters in range expressions, and the
                     characters included in the range, are determined by the current locale and the  values
                     of the LC_COLLATE or LC_ALL shell variables, if set.  To obtain the traditional inter‐
                     pretation of range expressions, where [a-d] is equivalent to [abcd], set value of  the
                     LC_ALL  shell  variable  to C, or enable the globasciiranges shell option.  A - may be
                     matched by including it as the first or last character in the set.  A ] may be matched
                     by including it as the first character in the set.

                     Within  [  and ], character classes can be specified using the syntax [:class:], where
                     class is one of the following classes defined in the POSIX standard:
                     alnum alpha ascii blank cntrl digit graph lower print punct space upper word xdigit
                     A character class matches any character belonging to that class.  The  word  character
                     class matches letters, digits, and the character _.

                     Within  [  and  ], an equivalence class can be specified using the syntax [=c=], which
                     matches all characters with the same collation weight (as defined by the  current  lo‐
                     cale) as the character c.

                     Within [ and ], the syntax [.symbol.] matches the collating symbol symbol.

       If  the  extglob  shell  option is enabled using the shopt builtin, the shell recognizes several ex‐
       tended pattern matching operators.  In the following description, a pattern-list is a list of one or
       more patterns separated by a |.  Composite patterns may be formed using one or more of the following
       sub-patterns:

              ?(pattern-list)
                     Matches zero or one occurrence of the given patterns
              *(pattern-list)
                     Matches zero or more occurrences of the given patterns
              +(pattern-list)
                     Matches one or more occurrences of the given patterns
              @(pattern-list)
                     Matches one of the given patterns
              !(pattern-list)
                     Matches anything except one of the given patterns

       Theextglob option changes the behavior of the parser, since the parentheses are normally treated  as
       operators  with  syntactic meaning.  To ensure that extended matching patterns are parsed correctly,
       make sure that extglob is enabled before parsing constructs containing the patterns, including shell
       functions and command substitutions.

       When  matching  filenames, the dotglob shell option determines the set of filenames that are tested:
       when dotglob is enabled, the set of filenames includes all files beginning with ``.'', but ``.'' and
       ``..''  must be matched by a pattern or sub-pattern that begins with a dot; when it is disabled, the
       set does not include any filenames beginning with ``.'' unless the  pattern  or  sub-pattern  begins
       with a ``.''.  As above, ``.'' only has a special meaning when matching filenames.

       Complicated  extended  pattern  matching  against long strings is slow, especially when the patterns
       contain alternations and the strings contain  multiple  matches.   Using  separate  matches  against
       shorter strings, or using arrays of strings instead of a single long string, may be faster.

   Quote Removal
       After  the preceding expansions, all unquoted occurrences of the characters \, ', and " that did not
       result from one of the above expansions are removed.

REDIRECTION
       Before a command is executed, its input and output may be redirected using a special notation inter‐
       preted  by  the  shell.  Redirection allows commands' file handles to be duplicated, opened, closed,
       made to refer to different files, and can change the files the command reads  from  and  writes  to.
       Redirection may also be used to modify file handles in the current shell execution environment.  The
       following redirection operators may precede or appear anywhere within a simple command or may follow
       a command.  Redirections are processed in the order they appear, from left to right.

       Each  redirection that may be preceded by a file descriptor number may instead be preceded by a word
       of the form {varname}.  In this case, for each redirection operator except >&- and  <&-,  the  shell
       will allocate a file descriptor greater than or equal to 10 and assign it to varname.  If >&- or <&-
       is preceded by {varname}, the value of varname defines the file descriptor to close.   If  {varname}
       is supplied, the redirection persists beyond the scope of the command, allowing the shell programmer
       to manage the file descriptor's lifetime manually.  The varredir_close shell option manages this be‐
       havior.

       In  the following descriptions, if the file descriptor number is omitted, and the first character of
       the redirection operator is <, the redirection refers to the standard input (file descriptor 0).  If
       the  first character of the redirection operator is >, the redirection refers to the standard output
       (file descriptor 1).

       The word following the redirection operator in the following descriptions, unless  otherwise  noted,
       is  subjected to brace expansion, tilde expansion, parameter and variable expansion, command substi‐
       tution, arithmetic expansion, quote removal, pathname expansion, and word splitting.  If it  expands
       to more than one word, bash reports an error.

       Note that the order of redirections is significant.  For example, the command

              ls > dirlist 2>&1

       directs both standard output and standard error to the file dirlist, while the command

              ls 2>&1 > dirlist

       directs only the standard output to file dirlist, because the standard error was duplicated from the
       standard output before the standard output was redirected to dirlist.

       Bash handles several filenames specially when they are used in redirections,  as  described  in  the
       following  table.   If  the  operating system on which bash is running provides these special files,
       bash will use them; otherwise it will emulate them internally with the behavior described below.

              /dev/fd/fd
                     If fd is a valid integer, file descriptor fd is duplicated.
              /dev/stdin
                     File descriptor 0 is duplicated.
              /dev/stdout
                     File descriptor 1 is duplicated.
              /dev/stderr
                     File descriptor 2 is duplicated.
              /dev/tcp/host/port
                     If host is a valid hostname or Internet address, and port is an integer port number or
                     service name, bash attempts to open the corresponding TCP socket.
              /dev/udp/host/port
                     If host is a valid hostname or Internet address, and port is an integer port number or
                     service name, bash attempts to open the corresponding UDP socket.

       A failure to open or create a file causes the redirection to fail.

       Redirections using file descriptors greater than 9 should be used with care, as  they  may  conflict
       with file descriptors the shell uses internally.

       Note that the exec builtin command can make redirections take effect in the current shell.

   Redirecting Input
       Redirection  of input causes the file whose name results from the expansion of word to be opened for
       reading on file descriptor n, or the standard input (file descriptor 0) if n is not specified.

       The general format for redirecting input is:

              [n]<word

   Redirecting Output
       Redirection of output causes the file whose name results from the expansion of word to be opened for
       writing  on file descriptor n, or the standard output (file descriptor 1) if n is not specified.  If
       the file does not exist it is created; if it does exist it is truncated to zero size.

       The general format for redirecting output is:

              [n]>word

       If the redirection operator is >, and the noclobber option to the set builtin has been enabled,  the
       redirection will fail if the file whose name results from the expansion of word exists and is a reg‐
       ular file.  If the redirection operator is >|, or the redirection operator is >  and  the  noclobber
       option  to  the  set  builtin  command is not enabled, the redirection is attempted even if the file
       named by word exists.

   Appending Redirected Output
       Redirection of output in this fashion causes the file whose name results from the expansion of  word
       to  be opened for appending on file descriptor n, or the standard output (file descriptor 1) if n is
       not specified.  If the file does not exist it is created.

       The general format for appending output is:

              [n]>>word

   Redirecting Standard Output and Standard Error
       This construct allows both the standard output (file descriptor 1) and  the  standard  error  output
       (file descriptor 2) to be redirected to the file whose name is the expansion of word.

       There are two formats for redirecting standard output and standard error:

              &>word
       and
              >&word

       Of the two forms, the first is preferred.  This is semantically equivalent to

              >word 2>&1

       When using the second form, word may not expand to a number or -.  If it does, other redirection op‐
       erators apply (see Duplicating File Descriptors below) for compatibility reasons.

   Appending Standard Output and Standard Error
       This construct allows both the standard output (file descriptor 1) and  the  standard  error  output
       (file descriptor 2) to be appended to the file whose name is the expansion of word.

       The format for appending standard output and standard error is:

              &>>word

       This is semantically equivalent to

              >>word 2>&1

       (see Duplicating File Descriptors below).

   Here Documents
       This type of redirection instructs the shell to read input from the current source until a line con‐
       taining only delimiter (with no trailing blanks) is seen.  All of the lines read up  to  that  point
       are then used as the standard input (or file descriptor n if n is specified) for a command.

       The format of here-documents is:

              [n]<<[-]word
                      here-document
              delimiter

       No  parameter and variable expansion, command substitution, arithmetic expansion, or pathname expan‐
       sion is performed on word.  If any part of word is quoted, the delimiter is the result of quote  re‐
       moval  on word, and the lines in the here-document are not expanded.  If word is unquoted, all lines
       of the here-document are subjected to parameter expansion, command substitution, and arithmetic  ex‐
       pansion, the character sequence \<newline> is ignored, and \ must be used to quote the characters \,
       $, and `.

       If the redirection operator is <<-, then all leading tab characters are stripped  from  input  lines
       and  the  line containing delimiter.  This allows here-documents within shell scripts to be indented
       in a natural fashion.

   Here Strings
       A variant of here documents, the format is:

              [n]<<<word

       The word undergoes tilde expansion, parameter and variable expansion, command  substitution,  arith‐
       metic  expansion,  and quote removal.  Pathname expansion and word splitting are not performed.  The
       result is supplied as a single string, with a newline appended, to the command on its standard input
       (or file descriptor n if n is specified).

   Duplicating File Descriptors
       The redirection operator

              [n]<&word

       is  used  to  duplicate input file descriptors.  If word expands to one or more digits, the file de‐
       scriptor denoted by n is made to be a copy of that file descriptor.  If the digits in  word  do  not
       specify  a file descriptor open for input, a redirection error occurs.  If word evaluates to -, file
       descriptor n is closed.  If n is not specified, the standard input (file descriptor 0) is used.

       The operator

              [n]>&word

       is used similarly to duplicate output file descriptors.  If n is not specified, the standard  output
       (file  descriptor  1) is used.  If the digits in word do not specify a file descriptor open for out‐
       put, a redirection error occurs.  If word evaluates to -, file descriptor n is closed.  As a special
       case,  if n is omitted, and word does not expand to one or more digits or -, the standard output and
       standard error are redirected as described previously.

   Moving File Descriptors
       The redirection operator

              [n]<&digit-

       moves the file descriptor digit to file descriptor n, or the standard input (file descriptor 0) if n
       is not specified.  digit is closed after being duplicated to n.

       Similarly, the redirection operator

              [n]>&digit-

       moves  the file descriptor digit to file descriptor n, or the standard output (file descriptor 1) if
       n is not specified.

   Opening File Descriptors for Reading and Writing
       The redirection operator

              [n]<>word

       causes the file whose name is the expansion of word to be opened for both  reading  and  writing  on
       file descriptor n, or on file descriptor 0 if n is not specified.  If the file does not exist, it is
       created.

ALIASES
       Aliases allow a string to be substituted for a word when it is used as the first word  of  a  simple
       command.  The shell maintains a list of aliases that may be set and unset with the alias and unalias
       builtin commands (see SHELL BUILTIN COMMANDS below).  The first word of each simple command, if  un‐
       quoted,  is  checked  to  see  if  it has an alias.  If so, that word is replaced by the text of the
       alias.  The characters /, $, `, and = and any of the  shell  metacharacters  or  quoting  characters
       listed  above may not appear in an alias name.  The replacement text may contain any valid shell in‐
       put, including shell metacharacters.  The first word of the replacement text is tested for  aliases,
       but  a  word that is identical to an alias being expanded is not expanded a second time.  This means
       that one may alias ls to ls -F, for instance, and bash does not try to recursively  expand  the  re‐
       placement  text.   If  the  last character of the alias value is a blank, then the next command word
       following the alias is also checked for alias expansion.

       Aliases are created and listed with the alias command, and removed with the unalias command.

       There is no mechanism for using arguments in the replacement text.  If arguments are needed,  use  a
       shell function (see FUNCTIONS below).

       Aliases  are  not expanded when the shell is not interactive, unless the expand_aliases shell option
       is set using shopt (see the description of shopt under SHELL BUILTIN COMMANDS below).

       The rules concerning the definition and use of aliases are somewhat confusing.  Bash always reads at
       least  one  complete  line of input, and all lines that make up a compound command, before executing
       any of the commands on that line or the compound command.  Aliases are expanded when  a  command  is
       read, not when it is executed.  Therefore, an alias definition appearing on the same line as another
       command does not take effect until the next line of input is read.  The commands following the alias
       definition  on  that  line  are  not affected by the new alias.  This behavior is also an issue when
       functions are executed.  Aliases are expanded when a function definition is read, not when the func‐
       tion  is executed, because a function definition is itself a command.  As a consequence, aliases de‐
       fined in a function are not available until after that function is executed.  To be safe, always put
       alias definitions on a separate line, and do not use alias in compound commands.

       For almost every purpose, aliases are superseded by shell functions.

FUNCTIONS
       A  shell  function,  defined as described above under SHELL GRAMMAR, stores a series of commands for
       later execution.  When the name of a shell function is used as a simple command name,  the  list  of
       commands  associated  with that function name is executed.  Functions are executed in the context of
       the current shell; no new process is created to interpret them (contrast this with the execution  of
       a  shell  script).  When a function is executed, the arguments to the function become the positional
       parameters during its execution.  The special parameter # is updated to reflect the change.  Special
       parameter  0  is  unchanged.   The  first element of the FUNCNAME variable is set to the name of the
       function while the function is executing.

       All other aspects of the shell execution environment are identical between a function and its caller
       with  these  exceptions:  the  DEBUG and RETURN traps (see the description of the trap builtin under
       SHELL BUILTIN COMMANDS below) are not inherited unless the function has been given the trace  attri‐
       bute  (see  the  description of the declare builtin below) or the -o functrace shell option has been
       enabled with the set builtin (in which case all functions inherit the DEBUG and RETURN  traps),  and
       the ERR trap is not inherited unless the -o errtrace shell option has been enabled.

       Variables  local  to  the function may be declared with the local builtin command (local variables).
       Ordinarily, variables and their values are shared between the function and its caller.  If  a  vari‐
       able is declared local, the variable's visible scope is restricted to that function and its children
       (including the functions it calls).

       In the following description, the current scope is a currently- executing function.  Previous scopes
       consist of that function's caller and so on, back to the "global" scope, where the shell is not exe‐
       cuting any shell function.  Consequently, a local variable at the current scope is  a  variable  de‐
       clared using the local or declare builtins in the function that is currently executing.

       Local  variables "shadow" variables with the same name declared at previous scopes.  For instance, a
       local variable declared in a function hides a global variable of the same name: references  and  as‐
       signments  refer  to  the local variable, leaving the global variable unmodified.  When the function
       returns, the global variable is once again visible.

       The shell uses dynamic scoping to control a variable's visibility within  functions.   With  dynamic
       scoping,  visible  variables  and  their  values are a result of the sequence of function calls that
       caused execution to reach the current function.  The value of a variable that a  function  sees  de‐
       pends  on  its value within its caller, if any, whether that caller is the "global" scope or another
       shell function.  This is also the value that a local variable declaration "shadows", and  the  value
       that is restored when the function returns.

       For example, if a variable var is declared as local in function func1, and func1 calls another func‐
       tion func2, references to var made from within func2 will resolve to the  local  variable  var  from
       func1, shadowing any global variable named var.

       The  unset  builtin  also  acts  using the same dynamic scope: if a variable is local to the current
       scope, unset will unset it; otherwise the unset will refer to the  variable  found  in  any  calling
       scope as described above.  If a variable at the current local scope is unset, it will remain so (ap‐
       pearing as unset) until it is reset in that scope or until the function returns.  Once the  function
       returns, any instance of the variable at a previous scope will become visible.  If the unset acts on
       a variable at a previous scope, any instance of a variable with that name  that  had  been  shadowed
       will become visible (see below how the localvar_unset shell option changes this behavior).

       The  FUNCNEST variable, if set to a numeric value greater than 0, defines a maximum function nesting
       level.  Function invocations that exceed the limit cause the entire command to abort.

       If the builtin command return is executed in a function, the function completes  and  execution  re‐
       sumes with the next command after the function call.  Any command associated with the RETURN trap is
       executed before execution resumes.  When a function completes, the values of the positional  parame‐
       ters  and the special parameter # are restored to the values they had prior to the function's execu‐
       tion.

       Function names and definitions may be listed with the -f option to the declare  or  typeset  builtin
       commands.  The -F option to declare or typeset will list the function names only (and optionally the
       source file and line number, if the extdebug shell option is enabled).  Functions may be exported so
       that  child shell processes (those created when executing a separate shell invocation) automatically
       have them defined with the -f option to the export builtin.  A function definition  may  be  deleted
       using the -f option to the unset builtin.

       Functions  may  be  recursive.  The FUNCNEST variable may be used to limit the depth of the function
       call stack and restrict the number of function invocations.  By default, no limit is imposed on  the
       number of recursive calls.

ARITHMETIC EVALUATION
       The  shell  allows  arithmetic expressions to be evaluated, under certain circumstances (see the let
       and declare builtin commands, the (( compound command, and  Arithmetic  Expansion).   Evaluation  is
       done in fixed-width integers with no check for overflow, though division by 0 is trapped and flagged
       as an error.  The operators and their precedence, associativity, and values are the same as in the C
       language.   The  following  list  of operators is grouped into levels of equal-precedence operators.
       The levels are listed in order of decreasing precedence.

       id++ id--
              variable post-increment and post-decrement
       - +    unary minus and plus
       ++id --id
              variable pre-increment and pre-decrement
       ! ~    logical and bitwise negation
       **     exponentiation
       * / %  multiplication, division, remainder
       + -    addition, subtraction
       << >>  left and right bitwise shifts
       <= >= < >
              comparison
       == !=  equality and inequality
       &      bitwise AND
       ^      bitwise exclusive OR
       |      bitwise OR
       &&     logical AND
       ||     logical OR
       expr?expr:expr
              conditional operator
       = *= /= %= += -= <<= >>= &= ^= |=
              assignment
       expr1 , expr2
              comma

       Shell variables are allowed as operands; parameter expansion is performed before the  expression  is
       evaluated.   Within  an expression, shell variables may also be referenced by name without using the
       parameter expansion syntax.  A shell variable that is null or unset evaluates to 0  when  referenced
       by  name  without  using the parameter expansion syntax.  The value of a variable is evaluated as an
       arithmetic expression when it is referenced, or when a variable which has been given the integer at‐
       tribute  using  declare -i is assigned a value.  A null value evaluates to 0.  A shell variable need
       not have its integer attribute turned on to be used in an expression.

       Integer constants follow the C language definition, without suffixes or character  constants.   Con‐
       stants  with  a leading 0 are interpreted as octal numbers.  A leading 0x or 0X denotes hexadecimal.
       Otherwise, numbers take the form [base#]n, where the optional base is a decimal number between 2 and
       64 representing the arithmetic base, and n is a number in that base.  If base# is omitted, then base
       10 is used.  When specifying n, if a non-digit is required, the digits greater  than  9  are  repre‐
       sented  by  the  lowercase letters, the uppercase letters, @, and _, in that order.  If base is less
       than or equal to 36, lowercase and uppercase letters may be used interchangeably to  represent  num‐
       bers between 10 and 35.

       Operators  are evaluated in order of precedence.  Sub-expressions in parentheses are evaluated first
       and may override the precedence rules above.

CONDITIONAL EXPRESSIONS
       Conditional expressions are used by the [[ compound command and the test and [ builtin  commands  to
       test  file attributes and perform string and arithmetic comparisons.  The test and [ commands deter‐
       mine their behavior based on the number of arguments; see the descriptions of those commands for any
       other command-specific actions.

       Expressions are formed from the following unary or binary primaries.  Bash handles several filenames
       specially when they are used in expressions.  If the operating system on which bash is running  pro‐
       vides  these  special files, bash will use them; otherwise it will emulate them internally with this
       behavior: If any file argument to one of the primaries is of the form /dev/fd/n, then file  descrip‐
       tor  n  is checked.  If the file argument to one of the primaries is one of /dev/stdin, /dev/stdout,
       or /dev/stderr, file descriptor 0, 1, or 2, respectively, is checked.

       Unless otherwise specified, primaries that operate on files follow symbolic links and operate on the
       target of the link, rather than the link itself.

       When  used with [[, the < and > operators sort lexicographically using the current locale.  The test
       command sorts using ASCII ordering.

       -a file
              True if file exists.
       -b file
              True if file exists and is a block special file.
       -c file
              True if file exists and is a character special file.
       -d file
              True if file exists and is a directory.
       -e file
              True if file exists.
       -f file
              True if file exists and is a regular file.
       -g file
              True if file exists and is set-group-id.
       -h file
              True if file exists and is a symbolic link.
       -k file
              True if file exists and its ``sticky'' bit is set.
       -p file
              True if file exists and is a named pipe (FIFO).
       -r file
              True if file exists and is readable.
       -s file
              True if file exists and has a size greater than zero.
       -t fd  True if file descriptor fd is open and refers to a terminal.
       -u file
              True if file exists and its set-user-id bit is set.
       -w file
              True if file exists and is writable.
       -x file
              True if file exists and is executable.
       -G file
              True if file exists and is owned by the effective group id.
       -L file
              True if file exists and is a symbolic link.
       -N file
              True if file exists and has been modified since it was last read.
       -O file
              True if file exists and is owned by the effective user id.
       -S file
              True if file exists and is a socket.
       file1 -ef file2
              True if file1 and file2 refer to the same device and inode numbers.
       file1 -nt file2
              True if file1 is newer (according to modification date) than file2, or if  file1  exists  and
              file2 does not.
       file1 -ot file2
              True if file1 is older than file2, or if file2 exists and file1 does not.
       -o optname
              True  if  the shell option optname is enabled.  See the list of options under the description
              of the -o option to the set builtin below.
       -v varname
              True if the shell variable varname is set (has been assigned a value).
       -R varname
              True if the shell variable varname is set and is a name reference.
       -z string
              True if the length of string is zero.
       string
       -n string
              True if the length of string is non-zero.

       string1 == string2
       string1 = string2
              True if the strings are equal.  = should be used with the test command for POSIX conformance.
              When  used  with  the [[ command, this performs pattern matching as described above (Compound
              Commands).

       string1 != string2
              True if the strings are not equal.

       string1 < string2
              True if string1 sorts before string2 lexicographically.

       string1 > string2
              True if string1 sorts after string2 lexicographically.

       arg1 OP arg2
              OP is one of -eq, -ne, -lt, -le, -gt, or -ge.  These arithmetic binary operators return  true
              if arg1 is equal to, not equal to, less than, less than or equal to, greater than, or greater
              than or equal to arg2, respectively.  Arg1 and arg2 may be  positive  or  negative  integers.
              When  used  with  the  [[ command, Arg1 and Arg2 are evaluated as arithmetic expressions (see
              ARITHMETIC EVALUATION above).

SIMPLE COMMAND EXPANSION
       When a simple command is executed, the shell performs the  following  expansions,  assignments,  and
       redirections, from left to right, in the following order.

       1.     The  words  that  the  parser has marked as variable assignments (those preceding the command
              name) and redirections are saved for later processing.

       2.     The words that are not variable assignments or redirections are expanded.  If any  words  re‐
              main after expansion, the first word is taken to be the name of the command and the remaining
              words are the arguments.

       3.     Redirections are performed as described above under REDIRECTION.

       4.     The text after the = in each variable assignment undergoes tilde expansion, parameter  expan‐
              sion,  command substitution, arithmetic expansion, and quote removal before being assigned to
              the variable.

       If no command name results, the variable assignments affect the current shell environment.   In  the
       case  of  such a command (one that consists only of assignment statements and redirections), assign‐
       ment statements are performed before redirections.  Otherwise, the variables are added to the  envi‐
       ronment  of the executed command and do not affect the current shell environment.  If any of the as‐
       signments attempts to assign a value to a readonly variable, an error occurs, and the command  exits
       with a non-zero status.

       If no command name results, redirections are performed, but do not affect the current shell environ‐
       ment.  A redirection error causes the command to exit with a non-zero status.

       If there is a command name left after expansion, execution proceeds as described below.   Otherwise,
       the  command  exits.   If one of the expansions contained a command substitution, the exit status of
       the command is the exit status of the last command substitution performed.  If there were no command
       substitutions, the command exits with a status of zero.

COMMAND EXECUTION
       After a command has been split into words, if it results in a simple command and an optional list of
       arguments, the following actions are taken.

       If the command name contains no slashes, the shell attempts to locate it.  If there exists  a  shell
       function  by  that name, that function is invoked as described above in FUNCTIONS.  If the name does
       not match a function, the shell searches for it in the list of shell builtins.  If a match is found,
       that builtin is invoked.

       If  the  name is neither a shell function nor a builtin, and contains no slashes, bash searches each
       element of the PATH for a directory containing an executable file by that name.  Bash  uses  a  hash
       table  to remember the full pathnames of executable files (see hash under SHELL BUILTIN COMMANDS be‐
       low).  A full search of the directories in PATH is performed only if the command is not found in the
       hash  table.   If  the search is unsuccessful, the shell searches for a defined shell function named
       command_not_found_handle.  If that function exists, it is invoked in a separate  execution  environ‐
       ment  with the original command and the original command's arguments as its arguments, and the func‐
       tion's exit status becomes the exit status of that subshell.  If that function is not  defined,  the
       shell prints an error message and returns an exit status of 127.

       If the search is successful, or if the command name contains one or more slashes, the shell executes
       the named program in a separate execution environment.  Argument 0 is set to the name given, and the
       remaining arguments to the command are set to the arguments given, if any.

       If  this  execution fails because the file is not in executable format, and the file is not a direc‐
       tory, it is assumed to be a shell script, a file containing shell commands, and the shell creates  a
       new  instance of itself to execute it.  This subshell reinitializes itself, so that the effect is as
       if a new shell had been invoked to handle the script, with the exception that the locations of  com‐
       mands  remembered  by  the  parent (see hash below under SHELL BUILTIN COMMANDS) are retained by the
       child.

       If the program is a file beginning with #!, the remainder of the first line specifies an interpreter
       for the program.  The shell executes the specified interpreter on operating systems that do not han‐
       dle this executable format themselves.  The arguments to the interpreter consist  of  a  single  op‐
       tional  argument  following  the  interpreter name on the first line of the program, followed by the
       name of the program, followed by the command arguments, if any.

COMMAND EXECUTION ENVIRONMENT
       The shell has an execution environment, which consists of the following:

       •      open files inherited by the shell at invocation, as modified by redirections supplied to  the
              exec builtin

       •      the  current working directory as set by cd, pushd, or popd, or inherited by the shell at in‐
              vocation

       •      the file creation mode mask as set by umask or inherited from the shell's parent

       •      current traps set by trap

       •      shell parameters that are set by variable assignment  or  with  set  or  inherited  from  the
              shell's parent in the environment

       •      shell functions defined during execution or inherited from the shell's parent in the environ‐
              ment

       •      options enabled at invocation (either by default or with command-line arguments) or by set

       •      options enabled by shopt

       •      shell aliases defined with alias

       •      various process IDs, including those of background jobs, the value of $$, and  the  value  of
              PPID

       When  a  simple command other than a builtin or shell function is to be executed, it is invoked in a
       separate execution environment that consists of the following.  Unless otherwise noted,  the  values
       are inherited from the shell.

       •      the shell's open files, plus any modifications and additions specified by redirections to the
              command

       •      the current working directory

       •      the file creation mode mask

       •      shell variables and functions marked for export, along with variables exported for  the  com‐
              mand, passed in the environment

       •      traps  caught  by  the  shell  are reset to the values inherited from the shell's parent, and
              traps ignored by the shell are ignored

       A command invoked in this separate environment cannot affect the shell's execution environment.

       A subshell is a copy of the shell process.

       Command substitution, commands grouped with parentheses, and asynchronous commands are invoked in  a
       subshell  environment  that is a duplicate of the shell environment, except that traps caught by the
       shell are reset to the values that the shell inherited from its parent at invocation.  Builtin  com‐
       mands  that  are invoked as part of a pipeline are also executed in a subshell environment.  Changes
       made to the subshell environment cannot affect the shell's execution environment.

       Subshells spawned to execute command substitutions inherit the value of the -e option from the  par‐
       ent shell.  When not in posix mode, bash clears the -e option in such subshells.

       If  a  command  is followed by a & and job control is not active, the default standard input for the
       command is the empty file /dev/null.  Otherwise, the invoked command inherits the  file  descriptors
       of the calling shell as modified by redirections.

ENVIRONMENT
       When a program is invoked it is given an array of strings called the environment.  This is a list of
       name-value pairs, of the form name=value.

       The shell provides several ways to manipulate the environment.  On invocation, the shell  scans  its
       own  environment and creates a parameter for each name found, automatically marking it for export to
       child processes.  Executed commands inherit the environment.  The export and declare -x commands al‐
       low parameters and functions to be added to and deleted from the environment.  If the value of a pa‐
       rameter in the environment is modified, the new value becomes part of the environment, replacing the
       old.  The environment inherited by any executed command consists of the shell's initial environment,
       whose values may be modified in the shell, less any pairs removed by the unset command, plus any ad‐
       ditions via the export and declare -x commands.

       The environment for any simple command or function may be augmented temporarily by prefixing it with
       parameter assignments, as described above in PARAMETERS.  These assignment  statements  affect  only
       the environment seen by that command.

       If  the  -k  option  is  set (see the set builtin command below), then all parameter assignments are
       placed in the environment for a command, not just those that precede the command name.

       When bash invokes an external command, the variable _ is set to the full filename of the command and
       passed to that command in its environment.

EXIT STATUS
       The  exit  status of an executed command is the value returned by the waitpid system call or equiva‐
       lent function.  Exit statuses fall between 0 and 255, though, as explained below, the shell may  use
       values  above  125 specially.  Exit statuses from shell builtins and compound commands are also lim‐
       ited to this range.  Under certain circumstances, the shell will use special values to indicate spe‐
       cific failure modes.

       For the shell's purposes, a command which exits with a zero exit status has succeeded.  An exit sta‐
       tus of zero indicates success.  A non-zero exit status indicates failure.  When a command terminates
       on a fatal signal N, bash uses the value of 128+N as the exit status.

       If  a  command  is not found, the child process created to execute it returns a status of 127.  If a
       command is found but is not executable, the return status is 126.

       If a command fails because of an error during expansion or redirection, the exit status  is  greater
       than zero.

       Shell  builtin  commands return a status of 0 (true) if successful, and non-zero (false) if an error
       occurs while they execute.  All builtins return an exit status of 2  to  indicate  incorrect  usage,
       generally invalid options or missing arguments.

       The exit status of the last command is available in the special parameter $?.

       Bash  itself  returns the exit status of the last command executed, unless a syntax error occurs, in
       which case it exits with a non-zero value.  See also the exit builtin command below.

SIGNALS
       When bash is interactive, in the absence of any traps, it ignores SIGTERM (so that kill 0  does  not
       kill an interactive shell), and SIGINT is caught and handled (so that the wait builtin is interrupt‐
       ible).  In all cases, bash ignores SIGQUIT.  If job control is  in  effect,  bash  ignores  SIGTTIN,
       SIGTTOU, and SIGTSTP.

       Non-builtin  commands run by bash have signal handlers set to the values inherited by the shell from
       its parent.  When job control is not in effect, asynchronous commands ignore SIGINT and  SIGQUIT  in
       addition  to  these inherited handlers.  Commands run as a result of command substitution ignore the
       keyboard-generated job control signals SIGTTIN, SIGTTOU, and SIGTSTP.

       The shell exits by default upon receipt of a SIGHUP.  Before exiting, an interactive  shell  resends
       the  SIGHUP  to all jobs, running or stopped.  Stopped jobs are sent SIGCONT to ensure that they re‐
       ceive the SIGHUP.  To prevent the shell from sending the signal to a particular job,  it  should  be
       removed  from the jobs table with the disown builtin (see SHELL BUILTIN COMMANDS below) or marked to
       not receive SIGHUP using disown -h.

       If the huponexit shell option has been set with shopt, bash sends a SIGHUP to all jobs when  an  in‐
       teractive login shell exits.

       If  bash  is  waiting for a command to complete and receives a signal for which a trap has been set,
       the trap will not be executed until the command completes.  When bash is waiting for an asynchronous
       command via the wait builtin, the reception of a signal for which a trap has been set will cause the
       wait builtin to return immediately with an exit status greater than 128, immediately after which the
       trap is executed.

       When job control is not enabled, and bash is waiting for a foreground command to complete, the shell
       receives keyboard-generated signals such as SIGINT (usually generated by ^C) that users commonly in‐
       tend  to  send  to  that  command.   This  happens because the shell and the command are in the same
       process group as the terminal, and ^C sends SIGINT to all processes in that process group.

       When bash is running without job control enabled and receives SIGINT while waiting for a  foreground
       command,  it  waits  until  that foreground command terminates and then decides what to do about the
       SIGINT:

       1.     If the command terminates due to the SIGINT, bash concludes that the user meant  to  end  the
              entire script, and acts on the SIGINT (e.g., by running a SIGINT trap or exiting itself);

       2.     If  the  command  does not terminate due to SIGINT, the program handled the SIGINT itself and
              did not treat it as a fatal signal.  In that case, bash does not treat SIGINT as a fatal sig‐
              nal, either, instead assuming that the SIGINT was used as part of the program's normal opera‐
              tion (e.g., emacs uses it to abort editing commands)  or  deliberately  discarded.   However,
              bash  will  run  any trap set on SIGINT, as it does with any other trapped signal it receives
              while it is waiting for the foreground command to complete, for compatibility.

JOB CONTROL
       Job control refers to the ability to selectively stop (suspend) the execution of processes and  con‐
       tinue  (resume) their execution at a later point.  A user typically employs this facility via an in‐
       teractive interface supplied jointly by the operating system kernel's terminal driver and bash.

       The shell associates a job with each pipeline.  It keeps a table of currently executing jobs,  which
       may  be listed with the jobs command.  When bash starts a job asynchronously (in the background), it
       prints a line that looks like:

              [1] 25647

       indicating that this job is job number 1 and that the process ID of the last process in the pipeline
       associated  with  this  job  is 25647.  All of the processes in a single pipeline are members of the
       same job.  Bash uses the job abstraction as the basis for job control.

       To facilitate the implementation of the user interface to job control, the  operating  system  main‐
       tains  the  notion of a current terminal process group ID.  Members of this process group (processes
       whose process group ID is equal to the current terminal process group ID) receive keyboard-generated
       signals such as SIGINT.  These processes are said to be in the foreground.  Background processes are
       those whose process group ID differs from the terminal's; such processes are immune to keyboard-gen‐
       erated  signals.   Only  foreground  processes are allowed to read from or, if the user so specifies
       with stty tostop, write to the terminal.  Background processes which attempt to read from (write  to
       when stty tostop is in effect) the terminal are sent a SIGTTIN (SIGTTOU) signal by the kernel's ter‐
       minal driver, which, unless caught, suspends the process.

       If the operating system on which bash is running supports job control, bash contains  facilities  to
       use  it.   Typing  the suspend character (typically ^Z, Control-Z) while a process is running causes
       that process to be stopped and returns control to bash.  Typing the delayed suspend character (typi‐
       cally ^Y, Control-Y) causes the process to be stopped when it attempts to read input from the termi‐
       nal, and control to be returned to bash.  The user may then manipulate the state of this job,  using
       the bg command to continue it in the background, the fg command to continue it in the foreground, or
       the kill command to kill it.  A ^Z takes effect immediately, and has the additional side  effect  of
       causing pending output and typeahead to be discarded.

       There  are a number of ways to refer to a job in the shell.  The character % introduces a job speci‐
       fication (jobspec).  Job number n may be referred to as %n.  A job may also be referred to  using  a
       prefix of the name used to start it, or using a substring that appears in its command line.  For ex‐
       ample, %ce refers to a stopped job whose command name begins with ce.  If a prefix matches more than
       one  job,  bash  reports  an error.  Using %?ce, on the other hand, refers to any job containing the
       string ce in its command line.  If the substring matches more than one job, bash reports  an  error.
       The  symbols %% and %+ refer to the shell's notion of the current job, which is the last job stopped
       while it was in the foreground or started in the background.  The previous job may be referenced us‐
       ing  %-.  If there is only a single job, %+ and %- can both be used to refer to that job.  In output
       pertaining to jobs (e.g., the output of the jobs command), the current job is always flagged with  a
       +,  and  the previous job with a -.  A single % (with no accompanying job specification) also refers
       to the current job.

       Simply naming a job can be used to bring it into the foreground: %1 is  a  synonym  for  ``fg  %1'',
       bringing  job  1  from the background into the foreground.  Similarly, ``%1 &'' resumes job 1 in the
       background, equivalent to ``bg %1''.

       The shell learns immediately whenever a job changes state.  Normally, bash waits until it  is  about
       to  print  a prompt before reporting changes in a job's status so as to not interrupt any other out‐
       put.  If the -b option to the set builtin command is enabled, bash reports such changes immediately.
       Any trap on SIGCHLD is executed for each child that exits.

       If  an  attempt  to  exit bash is made while jobs are stopped (or, if the checkjobs shell option has
       been enabled using the shopt builtin, running), the shell prints a  warning  message,  and,  if  the
       checkjobs  option  is enabled, lists the jobs and their statuses.  The jobs command may then be used
       to inspect their status.  If a second attempt to exit is made without an  intervening  command,  the
       shell does not print another warning, and any stopped jobs are terminated.

       When  the  shell is waiting for a job or process using the wait builtin, and job control is enabled,
       wait will return when the job changes state. The -f option causes wait to  wait  until  the  job  or
       process terminates before returning.

PROMPTING
       When  executing  interactively, bash displays the primary prompt PS1 when it is ready to read a com‐
       mand, and the secondary prompt PS2 when it needs more input to complete a  command.   Bash  displays
       PS0  after  it reads a command but before executing it.  Bash displays PS4 as described above before
       tracing each command when the -x option is enabled.  Bash allows these prompt strings to be  custom‐
       ized by inserting a number of backslash-escaped special characters that are decoded as follows:
              \a     an ASCII bell character (07)
              \d     the date in "Weekday Month Date" format (e.g., "Tue May 26")
              \D{format}
                     the format is passed to strftime(3) and the result is inserted into the prompt string;
                     an empty format results in a locale-specific time representation.  The braces are  re‐
                     quired
              \e     an ASCII escape character (033)
              \h     the hostname up to the first `.'
              \H     the hostname
              \j     the number of jobs currently managed by the shell
              \l     the basename of the shell's terminal device name
              \n     newline
              \r     carriage return
              \s     the name of the shell, the basename of $0 (the portion following the final slash)
              \t     the current time in 24-hour HH:MM:SS format
              \T     the current time in 12-hour HH:MM:SS format
              \@     the current time in 12-hour am/pm format
              \A     the current time in 24-hour HH:MM format
              \u     the username of the current user
              \v     the version of bash (e.g., 2.00)
              \V     the release of bash, version + patch level (e.g., 2.00.0)
              \w     the  value of the PWD shell variable ($PWD), with $HOME abbreviated with a tilde (uses
                     the value of the PROMPT_DIRTRIM variable)
              \W     the basename of $PWD, with $HOME abbreviated with a tilde
              \!     the history number of this command
              \#     the command number of this command
              \$     if the effective UID is 0, a #, otherwise a $
              \nnn   the character corresponding to the octal number nnn
              \\     a backslash
              \[     begin a sequence of non-printing characters, which could be used to embed  a  terminal
                     control sequence into the prompt
              \]     end a sequence of non-printing characters

       The  command number and the history number are usually different: the history number of a command is
       its position in the history list, which may include commands restored from  the  history  file  (see
       HISTORY below), while the command number is the position in the sequence of commands executed during
       the current shell session.  After the string is decoded, it is  expanded  via  parameter  expansion,
       command  substitution,  arithmetic expansion, and quote removal, subject to the value of the prompt‐
       vars shell option (see the description of the shopt command under  SHELL  BUILTIN  COMMANDS  below).
       This  can have unwanted side effects if escaped portions of the string appear within command substi‐
       tution or contain characters special to word expansion.

READLINE
       This is the library that handles reading input when using an interactive shell, unless the --noedit‐
       ing  option is given at shell invocation.  Line editing is also used when using the -e option to the
       read builtin.  By default, the line editing commands are similar to those of Emacs.  A vi-style line
       editing  interface is also available.  Line editing can be enabled at any time using the -o emacs or
       -o vi options to the set builtin (see SHELL BUILTIN COMMANDS below).  To turn off line editing after
       the shell is running, use the +o emacs or +o vi options to the set builtin.

   Readline Notation
       In this section, the Emacs-style notation is used to denote keystrokes.  Control keys are denoted by
       C-key, e.g., C-n means Control-N.  Similarly, meta keys are denoted by M-key, so M-x  means  Meta-X.
       (On  keyboards without a meta key, M-x means ESC x, i.e., press the Escape key then the x key.  This
       makes ESC the meta prefix.  The combination M-C-x means ESC-Control-x, or press the Escape key  then
       hold the Control key while pressing the x key.)

       Readline  commands may be given numeric arguments, which normally act as a repeat count.  Sometimes,
       however, it is the sign of the argument that is significant.  Passing a negative argument to a  com‐
       mand  that  acts in the forward direction (e.g., kill-line) causes that command to act in a backward
       direction.  Commands whose behavior with arguments deviates from this are noted below.

       When a command is described as killing text, the text deleted is saved for possible future retrieval
       (yanking).  The killed text is saved in a kill ring.  Consecutive kills cause the text to be accumu‐
       lated into one unit, which can be yanked all at once.  Commands which do not kill text separate  the
       chunks of text on the kill ring.

   Readline Initialization
       Readline  is  customized by putting commands in an initialization file (the inputrc file).  The name
       of this file is taken from the value of the INPUTRC variable.  If that variable is  unset,  the  de‐
       fault  is  ~/.inputrc.   If  that  file   does  not exist or cannot be read, the ultimate default is
       /etc/inputrc.  When a program which uses the readline library starts up, the initialization file  is
       read,  and the key bindings and variables are set.  There are only a few basic constructs allowed in
       the readline initialization file.  Blank lines are ignored.  Lines beginning with a # are  comments.
       Lines beginning with a $ indicate conditional constructs.  Other lines denote key bindings and vari‐
       able settings.

       The default key-bindings may be changed with an inputrc file.  Other programs that use this  library
       may add their own commands and bindings.

       For example, placing

              M-Control-u: universal-argument
       or
              C-Meta-u: universal-argument
       into the inputrc would make M-C-u execute the readline command universal-argument.

       The  following symbolic character names are recognized: RUBOUT, DEL, ESC, LFD, NEWLINE, RET, RETURN,
       SPC, SPACE, and TAB.

       In addition to command names, readline allows keys to be bound to a string that is inserted when the
       key is pressed (a macro).

   Readline Key Bindings
       The  syntax for controlling key bindings in the inputrc file is simple.  All that is required is the
       name of the command or the text of a macro and a key sequence to which it should be bound.  The name
       may  be  specified  in one of two ways: as a symbolic key name, possibly with Meta- or Control- pre‐
       fixes, or as a key sequence.

       When using the form keyname:function-name or macro, keyname is the name of a key spelled out in Eng‐
       lish.  For example:

              Control-u: universal-argument
              Meta-Rubout: backward-kill-word
              Control-o: "> output"

       In  the  above example, C-u is bound to the function universal-argument, M-DEL is bound to the func‐
       tion backward-kill-word, and C-o is bound to run the macro expressed on the right  hand  side  (that
       is, to insert the text ``> output'' into the line).

       In  the  second  form,  "keyseq":function-name  or  macro, keyseq differs from keyname above in that
       strings denoting an entire key sequence may be specified  by  placing  the  sequence  within  double
       quotes.  Some GNU Emacs style key escapes can be used, as in the following example, but the symbolic
       character names are not recognized.

              "\C-u": universal-argument
              "\C-x\C-r": re-read-init-file
              "\e[11~": "Function Key 1"

       In this example, C-u is again bound to the function universal-argument.  C-x C-r  is  bound  to  the
       function re-read-init-file, and ESC [ 1 1 ~ is bound to insert the text ``Function Key 1''.

       The full set of GNU Emacs style escape sequences is
              \C-    control prefix
              \M-    meta prefix
              \e     an escape character
              \\     backslash
              \"     literal "
              \'     literal '

       In addition to the GNU Emacs style escape sequences, a second set of backslash escapes is available:
              \a     alert (bell)
              \b     backspace
              \d     delete
              \f     form feed
              \n     newline
              \r     carriage return
              \t     horizontal tab
              \v     vertical tab
              \nnn   the eight-bit character whose value is the octal value nnn (one to three digits)
              \xHH   the  eight-bit  character whose value is the hexadecimal value HH (one or two hex dig‐
                     its)

       When entering the text of a macro, single or double quotes must be used to indicate a macro  defini‐
       tion.  Unquoted text is assumed to be a function name.  In the macro body, the backslash escapes de‐
       scribed above are expanded.  Backslash will quote any other character in the macro text, including "
       and '.

       Bash allows the current readline key bindings to be displayed or modified with the bind builtin com‐
       mand.  The editing mode may be switched during interactive use by using the -o  option  to  the  set
       builtin command (see SHELL BUILTIN COMMANDS below).

   Readline Variables
       Readline has variables that can be used to further customize its behavior.  A variable may be set in
       the inputrc file with a statement of the form

              set variable-name value
       or using the bind builtin command (see SHELL BUILTIN COMMANDS below).

       Except where noted, readline variables can take the values On or Off (without regard to case).   Un‐
       recognized  variable  names  are ignored.  When a variable value is read, empty or null values, "on"
       (case-insensitive), and "1" are equivalent to On.  All other values  are  equivalent  to  Off.   The
       variables and their default values are:

       active-region-start-color
              A string variable that controls the text color and background when displaying the text in the
              active region (see the description of enable-active-region below).  This string must not take
              up any physical character positions on the display, so it should consist only of terminal es‐
              cape sequences.  It is output to the terminal before displaying the text in  the  active  re‐
              gion.   This  variable is reset to the default value whenever the terminal type changes.  The
              default value is the string that puts the terminal in standout mode,  as  obtained  from  the
              terminal's terminfo description.  A sample value might be "\e[01;33m".
       active-region-end-color
              A  string  variable that "undoes" the effects of active-region-start-color and restores "nor‐
              mal" terminal display appearance after displaying text in the  active  region.   This  string
              must  not  take up any physical character positions on the display, so it should consist only
              of terminal escape sequences.  It is output to the terminal after displaying the text in  the
              active  region.   This  variable  is  reset  to  the default value whenever the terminal type
              changes.  The default value is the string that restores the terminal from standout  mode,  as
              obtained from the terminal's terminfo description.  A sample value might be "\e[0m".
       bell-style (audible)
              Controls  what  happens when readline wants to ring the terminal bell.  If set to none, read‐
              line never rings the bell.  If set to visible, readline uses a visible bell if one is  avail‐
              able.  If set to audible, readline attempts to ring the terminal's bell.
       bind-tty-special-chars (On)
              If  set to On, readline attempts to bind the control characters treated specially by the ker‐
              nel's terminal driver to their readline equivalents.
       blink-matching-paren (Off)
              If set to On, readline attempts to briefly move the cursor to an opening parenthesis  when  a
              closing parenthesis is inserted.
       colored-completion-prefix (Off)
              If  set  to  On,  when listing completions, readline displays the common prefix of the set of
              possible completions using a different color.  The color definitions are taken from the value
              of  the LS_COLORS environment variable.  If there is a color definition in $LS_COLORS for the
              custom suffix "readline-colored-completion-prefix", readline uses this color for  the  common
              prefix instead of its default.
       colored-stats (Off)
              If set to On, readline displays possible completions using different colors to indicate their
              file type.  The color definitions are taken from the value of the LS_COLORS environment vari‐
              able.
       comment-begin (``#'')
              The  string that is inserted when the readline insert-comment command is executed.  This com‐
              mand is bound to M-# in emacs mode and to # in vi command mode.
       completion-display-width (-1)
              The number of screen columns used to display possible  matches  when  performing  completion.
              The value is ignored if it is less than 0 or greater than the terminal screen width.  A value
              of 0 will cause matches to be displayed one per line.  The default value is -1.
       completion-ignore-case (Off)
              If set to On, readline performs filename matching and completion in a case-insensitive  fash‐
              ion.
       completion-map-case (Off)
              If  set  to On, and completion-ignore-case is enabled, readline treats hyphens (-) and under‐
              scores (_) as equivalent when performing case-insensitive filename matching and completion.
       completion-prefix-display-length (0)
              The length in characters of the common prefix of a list of possible completions that is  dis‐
              played  without  modification.  When set to a value greater than zero, common prefixes longer
              than this value are replaced with an ellipsis when displaying possible completions.
       completion-query-items (100)
              This determines when the user is queried about viewing the  number  of  possible  completions
              generated  by  the  possible-completions command.  It may be set to any integer value greater
              than or equal to zero.  If the number of possible completions is greater than or equal to the
              value of this variable, readline will ask whether or not the user wishes to view them; other‐
              wise they are simply listed on the terminal.  A zero value means readline should  never  ask;
              negative values are treated as zero.
       convert-meta (On)
              If  set  to  On, readline will convert characters with the eighth bit set to an ASCII key se‐
              quence by stripping the eighth bit and prefixing an escape character (in effect, using escape
              as  the  meta prefix).  The default is On, but readline will set it to Off if the locale con‐
              tains eight-bit characters.  This variable is dependent on the LC_CTYPE locale category,  and
              may change if the locale is changed.
       disable-completion (Off)
              If  set to On, readline will inhibit word completion.  Completion characters will be inserted
              into the line as if they had been mapped to self-insert.
       echo-control-characters (On)
              When set to On, on operating systems that indicate they support it, readline echoes a charac‐
              ter corresponding to a signal generated from the keyboard.
       editing-mode (emacs)
              Controls  whether  readline  begins with a set of key bindings similar to Emacs or vi.  edit‐
              ing-mode can be set to either emacs or vi.
       emacs-mode-string (@)
              If the show-mode-in-prompt variable is enabled, this string is displayed  immediately  before
              the last line of the primary prompt when emacs editing mode is active.  The value is expanded
              like a key binding, so the standard set of meta- and control prefixes  and  backslash  escape
              sequences is available.  Use the \1 and \2 escapes to begin and end sequences of non-printing
              characters, which can be used to embed a terminal control sequence into the mode string.
       enable-active-region (On)
              The point is the current cursor position, and mark refers to a saved  cursor  position.   The
              text  between  the point and mark is referred to as the region.  When this variable is set to
              On, readline allows certain commands to designate the region as active.  When the  region  is
              active,  readline  highlights  the  text  in  the  region  using  the value of the active-re‐
              gion-start-color, which defaults to the string that enables  the  terminal's  standout  mode.
              The  active  region shows the text inserted by bracketed-paste and any matching text found by
              incremental and non-incremental history searches.
       enable-bracketed-paste (On)
              When set to On, readline configures the terminal to insert each paste into the editing buffer
              as  a  single string of characters, instead of treating each character as if it had been read
              from the keyboard.  This prevents readline from executing any editing commands bound  to  key
              sequences appearing in the pasted text.
       enable-keypad (Off)
              When  set  to On, readline will try to enable the application keypad when it is called.  Some
              systems need this to enable the arrow keys.
       enable-meta-key (On)
              When set to On, readline will try to enable any meta modifier key the terminal claims to sup‐
              port  when  it  is called.  On many terminals, the meta key is used to send eight-bit charac‐
              ters.
       expand-tilde (Off)
              If set to On, tilde expansion is performed when readline attempts word completion.
       history-preserve-point (Off)
              If set to On, the history code attempts to place point at the same location on  each  history
              line retrieved with previous-history or next-history.
       history-size (unset)
              Set the maximum number of history entries saved in the history list.  If set to zero, any ex‐
              isting history entries are deleted and no new entries are saved.  If set to a value less than
              zero,  the  number  of history entries is not limited.  By default, the number of history en‐
              tries is set to the value of the HISTSIZE shell variable.  If an attempt is made to set  his‐
              tory-size to a non-numeric value, the maximum number of history entries will be set to 500.
       horizontal-scroll-mode (Off)
              When  set  to  On, makes readline use a single line for display, scrolling the input horizon‐
              tally on a single screen line when it becomes longer than the screen width rather than  wrap‐
              ping to a new line.  This setting is automatically enabled for terminals of height 1.
       input-meta (Off)
              If set to On, readline will enable eight-bit input (that is, it will not strip the eighth bit
              from the characters it reads), regardless of what the terminal claims it  can  support.   The
              name  meta-flag is a synonym for this variable.  The default is Off, but readline will set it
              to On if the locale contains  eight-bit  characters.   This  variable  is  dependent  on  the
              LC_CTYPE locale category, and may change if the locale is changed.
       isearch-terminators (``C-[C-J'')
              The string of characters that should terminate an incremental search without subsequently ex‐
              ecuting the character as a command.  If this variable has not been given a value, the charac‐
              ters ESC and C-J will terminate an incremental search.
       keymap (emacs)
              Set  the  current  readline  keymap.  The set of valid keymap names is emacs, emacs-standard,
              emacs-meta, emacs-ctlx, vi, vi-command, and vi-insert.  vi is equivalent to vi-command; emacs
              is  equivalent to emacs-standard.  The default value is emacs; the value of editing-mode also
              affects the default keymap.
       keyseq-timeout (500)
              Specifies the duration readline will wait for a character when reading an ambiguous  key  se‐
              quence  (one  that  can form a complete key sequence using the input read so far, or can take
              additional input to complete a longer key sequence).  If no  input  is  received  within  the
              timeout,  readline will use the shorter but complete key sequence.  The value is specified in
              milliseconds, so a value of 1000 means that readline will wait one second for additional  in‐
              put.   If  this  variable  is  set to a value less than or equal to zero, or to a non-numeric
              value, readline will wait until another key is pressed to decide which key sequence  to  com‐
              plete.
       mark-directories (On)
              If set to On, completed directory names have a slash appended.
       mark-modified-lines (Off)
              If  set  to On, history lines that have been modified are displayed with a preceding asterisk
              (*).
       mark-symlinked-directories (Off)
              If set to On, completed names which are symbolic links to directories have a  slash  appended
              (subject to the value of mark-directories).
       match-hidden-files (On)
              This  variable,  when  set to On, causes readline to match files whose names begin with a `.'
              (hidden files) when performing filename completion.  If set to Off, the leading `.'  must  be
              supplied by the user in the filename to be completed.
       menu-complete-display-prefix (Off)
              If  set to On, menu completion displays the common prefix of the list of possible completions
              (which may be empty) before cycling through the list.
       output-meta (Off)
              If set to On, readline will display characters with the eighth bit set directly  rather  than
              as  a  meta-prefixed  escape sequence.  The default is Off, but readline will set it to On if
              the locale contains eight-bit characters.  This variable is dependent on the LC_CTYPE  locale
              category, and may change if the locale is changed.
       page-completions (On)
              If  set  to  On, readline uses an internal more-like pager to display a screenful of possible
              completions at a time.
       print-completions-horizontally (Off)
              If set to On, readline will display completions with matches sorted horizontally in alphabet‐
              ical order, rather than down the screen.
       revert-all-at-newline (Off)
              If  set  to  On,  readline  will  undo all changes to history lines before returning when ac‐
              cept-line is executed.  By default, history lines may be modified and retain individual  undo
              lists across calls to readline.
       show-all-if-ambiguous (Off)
              This alters the default behavior of the completion functions.  If set to On, words which have
              more than one possible completion cause the matches to be listed immediately instead of ring‐
              ing the bell.
       show-all-if-unmodified (Off)
              This  alters  the  default  behavior  of  the  completion  functions  in a fashion similar to
              show-all-if-ambiguous.  If set to On, words which have  more  than  one  possible  completion
              without  any  possible partial completion (the possible completions don't share a common pre‐
              fix) cause the matches to be listed immediately instead of ringing the bell.
       show-mode-in-prompt (Off)
              If set to On, add a string to the beginning of the prompt indicating the editing mode: emacs,
              vi command, or vi insertion.  The mode strings are user-settable (e.g., emacs-mode-string).
       skip-completed-text (Off)
              If  set to On, this alters the default completion behavior when inserting a single match into
              the line.  It's only active when performing completion in the middle of a word.  If  enabled,
              readline  does not insert characters from the completion that match characters after point in
              the word being completed, so portions of the word following the cursor are not duplicated.
       vi-cmd-mode-string ((cmd))
              If the show-mode-in-prompt variable is enabled, this string is displayed  immediately  before
              the  last line of the primary prompt when vi editing mode is active and in command mode.  The
              value is expanded like a key binding, so the standard set of meta- and control  prefixes  and
              backslash  escape  sequences  is  available.   Use the \1 and \2 escapes to begin and end se‐
              quences of non-printing characters, which can be used to embed a  terminal  control  sequence
              into the mode string.
       vi-ins-mode-string ((ins))
              If  the  show-mode-in-prompt variable is enabled, this string is displayed immediately before
              the last line of the primary prompt when vi editing mode is active  and  in  insertion  mode.
              The  value  is expanded like a key binding, so the standard set of meta- and control prefixes
              and backslash escape sequences is available.  Use the \1 and \2 escapes to begin and end  se‐
              quences  of  non-printing  characters, which can be used to embed a terminal control sequence
              into the mode string.
       visible-stats (Off)
              If set to On, a character denoting a file's type as reported by stat(2) is  appended  to  the
              filename when listing possible completions.

   Readline Conditional Constructs
       Readline  implements  a  facility similar in spirit to the conditional compilation features of the C
       preprocessor which allows key bindings and variable settings to be performed as the result of tests.
       There are four parser directives used.

       $if    The  $if  construct  allows bindings to be made based on the editing mode, the terminal being
              used, or the application using readline.  The text of the test, after any  comparison  opera‐
              tor,
               extends  to  the end of the line; unless otherwise noted, no characters are required to iso‐
              late it.

              mode   The mode= form of the $if directive is used to test whether readline is in emacs or vi
                     mode.   This  may be used in conjunction with the set keymap command, for instance, to
                     set bindings in the emacs-standard and emacs-ctlx keymaps only if readline is starting
                     out in emacs mode.

              term   The  term= form may be used to include terminal-specific key bindings, perhaps to bind
                     the key sequences output by the terminal's function keys.  The word on the right  side
                     of  the  = is tested against both the full name of the terminal and the portion of the
                     terminal name before the first -.  This allows sun to match both sun and sun-cmd,  for
                     instance.

              version
                     The  version  test  may  be used to perform comparisons against specific readline ver‐
                     sions.  The version expands to the current readline version.  The  set  of  comparison
                     operators  includes =, (and ==), !=, <=, >=, <, and >.  The version number supplied on
                     the right side of the operator consists of a major version number, an optional decimal
                     point,  and an optional minor version (e.g., 7.1). If the minor version is omitted, it
                     is assumed to be 0.  The operator may be separated from the string  version  and  from
                     the version number argument by whitespace.

              application
                     The application construct is used to include application-specific settings.  Each pro‐
                     gram using the readline library sets the application name, and an initialization  file
                     can  test  for  a particular value.  This could be used to bind key sequences to func‐
                     tions useful for a specific program.  For instance, the following command adds  a  key
                     sequence that quotes the current or previous word in bash:

                     $if Bash
                     # Quote the current or previous word
                     "\C-xq": "\eb\"\ef\""
                     $endif

              variable
                     The  variable construct provides simple equality tests for readline variables and val‐
                     ues.  The permitted comparison operators are =, ==, and !=.  The variable name must be
                     separated  from  the  comparison operator by whitespace; the operator may be separated
                     from the value on the right hand side by whitespace.  Both string  and  boolean  vari‐
                     ables may be tested. Boolean variables must be tested against the values on and off.

       $endif This command, as seen in the previous example, terminates an $if command.

       $else  Commands in this branch of the $if directive are executed if the test fails.

       $include
              This  directive  takes  a single filename as an argument and reads commands and bindings from
              that file.  For example, the following directive would read /etc/inputrc:

              $include  /etc/inputrc

   Searching
       Readline provides commands for searching through the command history (see HISTORY below)  for  lines
       containing a specified string.  There are two search modes: incremental and non-incremental.

       Incremental searches begin before the user has finished typing the search string.  As each character
       of the search string is typed, readline displays the next entry from the history matching the string
       typed  so far.  An incremental search requires only as many characters as needed to find the desired
       history entry.  The characters present in the value of the isearch-terminators variable are used  to
       terminate an incremental search.  If that variable has not been assigned a value the Escape and Con‐
       trol-J characters will terminate an incremental search.  Control-G will abort an incremental  search
       and  restore  the  original  line.   When the search is terminated, the history entry containing the
       search string becomes the current line.

       To find other matching entries in the history list, type  Control-S  or  Control-R  as  appropriate.
       This  will  search  backward or forward in the history for the next entry matching the search string
       typed so far.  Any other key sequence bound to a readline command will terminate the search and exe‐
       cute  that  command.  For instance, a newline will terminate the search and accept the line, thereby
       executing the command from the history list.

       Readline remembers the last incremental search string.  If two Control-Rs are typed without any  in‐
       tervening characters defining a new search string, any remembered search string is used.

       Non-incremental  searches  read the entire search string before starting to search for matching his‐
       tory lines.  The search string may be typed by the user or be part of the contents  of  the  current
       line.

   Readline Command Names
       The following is a list of the names of the commands and the default key sequences to which they are
       bound.  Command names without an accompanying key sequence are unbound by default.  In the following
       descriptions,  point  refers  to  the  current cursor position, and mark refers to a cursor position
       saved by the set-mark command.  The text between the point and mark is referred to as the region.

   Commands for Moving
       beginning-of-line (C-a)
              Move to the start of the current line.
       end-of-line (C-e)
              Move to the end of the line.
       forward-char (C-f)
              Move forward a character.
       backward-char (C-b)
              Move back a character.
       forward-word (M-f)
              Move forward to the end of the next word.  Words  are  composed  of  alphanumeric  characters
              (letters and digits).
       backward-word (M-b)
              Move  back  to the start of the current or previous word.  Words are composed of alphanumeric
              characters (letters and digits).
       shell-forward-word
              Move forward to the end of the next word.  Words are delimited by non-quoted shell  metachar‐
              acters.
       shell-backward-word
              Move  back  to  the start of the current or previous word.  Words are delimited by non-quoted
              shell metacharacters.
       previous-screen-line
              Attempt to move point to the same physical screen column  on  the  previous  physical  screen
              line.  This  will  not  have the desired effect if the current readline line does not take up
              more than one physical line or if point is not greater than the length of the prompt plus the
              screen width.
       next-screen-line
              Attempt  to  move  point to the same physical screen column on the next physical screen line.
              This will not have the desired effect if the current readline line does not take up more than
              one  physical  line  or  if  the  length of the current readline line is not greater than the
              length of the prompt plus the screen width.
       clear-display (M-C-l)
              Clear the screen and, if possible, the terminal's scrollback buffer, then redraw the  current
              line, leaving the current line at the top of the screen.
       clear-screen (C-l)
              Clear  the  screen,  then redraw the current line, leaving the current line at the top of the
              screen.  With an argument, refresh the current line without clearing the screen.
       redraw-current-line
              Refresh the current line.

   Commands for Manipulating the History
       accept-line (Newline, Return)
              Accept the line regardless of where the cursor is.  If this line is non-empty, add it to  the
              history  list  according to the state of the HISTCONTROL variable.  If the line is a modified
              history line, then restore the history line to its original state.
       previous-history (C-p)
              Fetch the previous command from the history list, moving back in the list.
       next-history (C-n)
              Fetch the next command from the history list, moving forward in the list.
       beginning-of-history (M-<)
              Move to the first line in the history.
       end-of-history (M->)
              Move to the end of the input history, i.e., the line currently being entered.
       operate-and-get-next (C-o)
              Accept the current line for execution and fetch the next line relative to  the  current  line
              from  the  history for editing.  A numeric argument, if supplied, specifies the history entry
              to use instead of the current line.
       fetch-history
              With a numeric argument, fetch that entry from the history list and make it the current line.
              Without an argument, move back to the first entry in the history list.
       reverse-search-history (C-r)
              Search  backward  starting  at the current line and moving `up' through the history as neces‐
              sary.  This is an incremental search.
       forward-search-history (C-s)
              Search forward starting at the current line and moving `down' through the history  as  neces‐
              sary.  This is an incremental search.
       non-incremental-reverse-search-history (M-p)
              Search  backward  through  the  history  starting at the current line using a non-incremental
              search for a string supplied by the user.
       non-incremental-forward-search-history (M-n)
              Search forward through the history using a non-incremental search for a  string  supplied  by
              the user.
       history-search-forward
              Search forward through the history for the string of characters between the start of the cur‐
              rent line and the point.  This is a non-incremental search.
       history-search-backward
              Search backward through the history for the string of characters between  the  start  of  the
              current line and the point.  This is a non-incremental search.
       history-substring-search-backward
              Search  backward  through  the  history for the string of characters between the start of the
              current line and the current cursor position (the point).  The search string may  match  any‐
              where in a history line.  This is a non-incremental search.
       history-substring-search-forward
              Search forward through the history for the string of characters between the start of the cur‐
              rent line and the point.  The search string may match anywhere in a history line.  This is  a
              non-incremental search.
       yank-nth-arg (M-C-y)
              Insert  the  first  argument to the previous command (usually the second word on the previous
              line) at point.  With an argument n, insert the nth word from the previous command (the words
              in  the  previous  command begin with word 0).  A negative argument inserts the nth word from
              the end of the previous command.  Once the argument n is computed, the argument is  extracted
              as if the "!n" history expansion had been specified.
       yank-last-arg (M-., M-_)
              Insert  the  last argument to the previous command (the last word of the previous history en‐
              try).  With a numeric argument,  behave  exactly  like  yank-nth-arg.   Successive  calls  to
              yank-last-arg move back through the history list, inserting the last word (or the word speci‐
              fied by the argument to the first call) of each line in turn.  Any numeric argument  supplied
              to  these  successive calls determines the direction to move through the history.  A negative
              argument switches the direction through the history (back or forward).  The history expansion
              facilities are used to extract the last word, as if the "!$" history expansion had been spec‐
              ified.
       shell-expand-line (M-C-e)
              Expand the line as the shell does.  This performs alias and history expansion as well as  all
              of  the  shell word expansions.  See HISTORY EXPANSION below for a description of history ex‐
              pansion.
       history-expand-line (M-^)
              Perform history expansion on the current line.  See HISTORY EXPANSION below for a description
              of history expansion.
       magic-space
              Perform  history expansion on the current line and insert a space.  See HISTORY EXPANSION be‐
              low for a description of history expansion.
       alias-expand-line
              Perform alias expansion on the current line.  See ALIASES above for a  description  of  alias
              expansion.
       history-and-alias-expand-line
              Perform history and alias expansion on the current line.
       insert-last-argument (M-., M-_)
              A synonym for yank-last-arg.
       edit-and-execute-command (C-x C-e)
              Invoke an editor on the current command line, and execute the result as shell commands.  Bash
              attempts to invoke $VISUAL, $EDITOR, and emacs as the editor, in that order.

   Commands for Changing Text
       end-of-file (usually C-d)
              The character indicating end-of-file as set, for example, by ``stty''.  If this character  is
              read  when  there  are  no characters on the line, and point is at the beginning of the line,
              readline interprets it as the end of input and returns EOF.
       delete-char (C-d)
              Delete the character at point.  If this function is bound to the same character  as  the  tty
              EOF character, as C-d commonly is, see above for the effects.
       backward-delete-char (Rubout)
              Delete the character behind the cursor.  When given a numeric argument, save the deleted text
              on the kill ring.
       forward-backward-delete-char
              Delete the character under the cursor, unless the cursor is at the end of the line, in  which
              case the character behind the cursor is deleted.
       quoted-insert (C-q, C-v)
              Add  the  next  character  typed to the line verbatim.  This is how to insert characters like
              C-q, for example.
       tab-insert (C-v TAB)
              Insert a tab character.
       self-insert (a, b, A, 1, !, ...)
              Insert the character typed.
       transpose-chars (C-t)
              Drag the character before point forward over the character at point, moving point forward  as
              well.   If  point  is  at the end of the line, then this transposes the two characters before
              point.  Negative arguments have no effect.
       transpose-words (M-t)
              Drag the word before point past the word after point, moving point over that  word  as  well.
              If point is at the end of the line, this transposes the last two words on the line.
       upcase-word (M-u)
              Uppercase  the current (or following) word.  With a negative argument, uppercase the previous
              word, but do not move point.
       downcase-word (M-l)
              Lowercase the current (or following) word.  With a negative argument, lowercase the  previous
              word, but do not move point.
       capitalize-word (M-c)
              Capitalize  the current (or following) word.  With a negative argument, capitalize the previ‐
              ous word, but do not move point.
       overwrite-mode
              Toggle overwrite mode.  With an explicit positive numeric  argument,  switches  to  overwrite
              mode.  With an explicit non-positive numeric argument, switches to insert mode.  This command
              affects only emacs mode; vi mode does overwrite differently.  Each call to readline()  starts
              in insert mode.  In overwrite mode, characters bound to self-insert replace the text at point
              rather than pushing the text to the right.  Characters bound to backward-delete-char  replace
              the character before point with a space.  By default, this command is unbound.

   Killing and Yanking
       kill-line (C-k)
              Kill the text from point to the end of the line.
       backward-kill-line (C-x Rubout)
              Kill backward to the beginning of the line.
       unix-line-discard (C-u)
              Kill backward from point to the beginning of the line.  The killed text is saved on the kill-
              ring.
       kill-whole-line
              Kill all characters on the current line, no matter where point is.
       kill-word (M-d)
              Kill from point to the end of the current word, or if between words, to the end of  the  next
              word.  Word boundaries are the same as those used by forward-word.
       backward-kill-word (M-Rubout)
              Kill the word behind point.  Word boundaries are the same as those used by backward-word.
       shell-kill-word
              Kill  from  point to the end of the current word, or if between words, to the end of the next
              word.  Word boundaries are the same as those used by shell-forward-word.
       shell-backward-kill-word
              Kill the word behind point.  Word boundaries are  the  same  as  those  used  by  shell-back‐
              ward-word.
       unix-word-rubout (C-w)
              Kill  the  word behind point, using white space as a word boundary.  The killed text is saved
              on the kill-ring.
       unix-filename-rubout
              Kill the word behind point, using white space and the slash character as the word boundaries.
              The killed text is saved on the kill-ring.
       delete-horizontal-space (M-\)
              Delete all spaces and tabs around point.
       kill-region
              Kill the text in the current region.
       copy-region-as-kill
              Copy the text in the region to the kill buffer.
       copy-backward-word
              Copy  the  word  before  point to the kill buffer.  The word boundaries are the same as back‐
              ward-word.
       copy-forward-word
              Copy the word following point to the kill buffer.  The word boundaries are the same  as  for‐
              ward-word.
       yank (C-y)
              Yank the top of the kill ring into the buffer at point.
       yank-pop (M-y)
              Rotate the kill ring, and yank the new top.  Only works following yank or yank-pop.

   Numeric Arguments
       digit-argument (M-0, M-1, ..., M--)
              Add  this  digit to the argument already accumulating, or start a new argument.  M-- starts a
              negative argument.
       universal-argument
              This is another way to specify an argument.  If this command is followed by one or more  dig‐
              its,  optionally with a leading minus sign, those digits define the argument.  If the command
              is followed by digits, executing universal-argument again ends the numeric argument,  but  is
              otherwise ignored.  As a special case, if this command is immediately followed by a character
              that is neither a digit nor minus sign, the argument count for the next command is multiplied
              by  four.   The  argument  count  is initially one, so executing this function the first time
              makes the argument count four, a second time makes the argument count sixteen, and so on.

   Completing
       complete (TAB)
              Attempt to perform completion on the text before point.  Bash  attempts  completion  treating
              the  text  as  a  variable (if the text begins with $), username (if the text begins with ~),
              hostname (if the text begins with @), or command (including aliases and functions)  in  turn.
              If none of these produces a match, filename completion is attempted.
       possible-completions (M-?)
              List the possible completions of the text before point.
       insert-completions (M-*)
              Insert  all  completions  of  the  text before point that would have been generated by possi‐
              ble-completions.
       menu-complete
              Similar to complete, but replaces the word to be completed with a single match from the  list
              of  possible completions.  Repeated execution of menu-complete steps through the list of pos‐
              sible completions, inserting each match in turn.  At the end of the list of completions,  the
              bell  is  rung  (subject to the setting of bell-style) and the original text is restored.  An
              argument of n moves n positions forward in the list of matches; a negative  argument  may  be
              used  to move backward through the list.  This command is intended to be bound to TAB, but is
              unbound by default.
       menu-complete-backward
              Identical to menu-complete, but moves backward through the list of possible  completions,  as
              if menu-complete had been given a negative argument.  This command is unbound by default.
       delete-char-or-list
              Deletes  the  character  under  the  cursor  if not at the beginning or end of the line (like
              delete-char).  If at the end of the line, behaves identically to possible-completions.   This
              command is unbound by default.
       complete-filename (M-/)
              Attempt filename completion on the text before point.
       possible-filename-completions (C-x /)
              List the possible completions of the text before point, treating it as a filename.
       complete-username (M-~)
              Attempt completion on the text before point, treating it as a username.
       possible-username-completions (C-x ~)
              List the possible completions of the text before point, treating it as a username.
       complete-variable (M-$)
              Attempt completion on the text before point, treating it as a shell variable.
       possible-variable-completions (C-x $)
              List the possible completions of the text before point, treating it as a shell variable.
       complete-hostname (M-@)
              Attempt completion on the text before point, treating it as a hostname.
       possible-hostname-completions (C-x @)
              List the possible completions of the text before point, treating it as a hostname.
       complete-command (M-!)
              Attempt  completion on the text before point, treating it as a command name.  Command comple‐
              tion attempts to match the text against  aliases,  reserved  words,  shell  functions,  shell
              builtins, and finally executable filenames, in that order.
       possible-command-completions (C-x !)
              List the possible completions of the text before point, treating it as a command name.
       dynamic-complete-history (M-TAB)
              Attempt  completion  on the text before point, comparing the text against lines from the his‐
              tory list for possible completion matches.
       dabbrev-expand
              Attempt menu completion on the text before point, comparing the text against lines  from  the
              history list for possible completion matches.
       complete-into-braces (M-{)
              Perform  filename  completion  and  insert  the  list of possible completions enclosed within
              braces so the list is available to the shell (see Brace Expansion above).

   Keyboard Macros
       start-kbd-macro (C-x ()
              Begin saving the characters typed into the current keyboard macro.
       end-kbd-macro (C-x ))
              Stop saving the characters typed into the current keyboard macro and store the definition.
       call-last-kbd-macro (C-x e)
              Re-execute the last keyboard macro defined, by making the characters in the macro  appear  as
              if typed at the keyboard.
       print-last-kbd-macro ()
              Print the last keyboard macro defined in a format suitable for the inputrc file.

   Miscellaneous
       re-read-init-file (C-x C-r)
              Read  in  the  contents of the inputrc file, and incorporate any bindings or variable assign‐
              ments found there.
       abort (C-g)
              Abort the current editing command and ring the terminal's bell (subject  to  the  setting  of
              bell-style).
       do-lowercase-version (M-A, M-B, M-x, ...)
              If  the metafied character x is uppercase, run the command that is bound to the corresponding
              metafied lowercase character.  The behavior is undefined if x is already lowercase.
       prefix-meta (ESC)
              Metafy the next character typed.  ESC f is equivalent to Meta-f.
       undo (C-_, C-x C-u)
              Incremental undo, separately remembered for each line.
       revert-line (M-r)
              Undo all changes made to this line.  This is like executing the undo command enough times  to
              return the line to its initial state.
       tilde-expand (M-&)
              Perform tilde expansion on the current word.
       set-mark (C-@, M-<space>)
              Set  the mark to the point.  If a numeric argument is supplied, the mark is set to that posi‐
              tion.
       exchange-point-and-mark (C-x C-x)
              Swap the point with the mark.  The current cursor position is set to the saved position,  and
              the old cursor position is saved as the mark.
       character-search (C-])
              A  character is read and point is moved to the next occurrence of that character.  A negative
              argument searches for previous occurrences.
       character-search-backward (M-C-])
              A character is read and point is moved to the previous occurrence of that character.  A nega‐
              tive argument searches for subsequent occurrences.
       skip-csi-sequence
              Read  enough  characters  to consume a multi-key sequence such as those defined for keys like
              Home and End.  Such sequences begin with a Control Sequence Indicator (CSI),  usually  ESC-[.
              If  this  sequence is bound to "\[", keys producing such sequences will have no effect unless
              explicitly bound to a readline command, instead of inserting stray characters into the  edit‐
              ing buffer.  This is unbound by default, but usually bound to ESC-[.
       insert-comment (M-#)
              Without  a  numeric argument, the value of the readline comment-begin variable is inserted at
              the beginning of the current line.  If a numeric argument is supplied, this command acts as a
              toggle:  if the characters at the beginning of the line do not match the value of comment-be‐
              gin, the value is inserted, otherwise the characters in comment-begin are  deleted  from  the
              beginning  of the line.  In either case, the line is accepted as if a newline had been typed.
              The default value of comment-begin causes this command to make the current line a shell  com‐
              ment.  If a numeric argument causes the comment character to be removed, the line will be ex‐
              ecuted by the shell.
       spell-correct-word (C-x s)
              Perform spelling correction on the current word, treating it as a directory or  filename,  in
              the  same  way  as  the  cdspell shell option.  Word boundaries are the same as those used by
              shell-forward-word.
       glob-complete-word (M-g)
              The word before point is treated as a pattern for pathname expansion, with  an  asterisk  im‐
              plicitly  appended.  This pattern is used to generate a list of matching filenames for possi‐
              ble completions.
       glob-expand-word (C-x *)
              The word before point is treated as a pattern for pathname expansion, and the list of  match‐
              ing  filenames is inserted, replacing the word.  If a numeric argument is supplied, an aster‐
              isk is appended before pathname expansion.
       glob-list-expansions (C-x g)
              The list of expansions that would have been generated by glob-expand-word is  displayed,  and
              the line is redrawn.  If a numeric argument is supplied, an asterisk is appended before path‐
              name expansion.
       dump-functions
              Print all of the functions and their key bindings to the readline output stream.   If  a  nu‐
              meric argument is supplied, the output is formatted in such a way that it can be made part of
              an inputrc file.
       dump-variables
              Print all of the settable readline variables and their values to the readline output  stream.
              If  a numeric argument is supplied, the output is formatted in such a way that it can be made
              part of an inputrc file.
       dump-macros
              Print all of the readline key sequences bound to macros and the strings they  output.   If  a
              numeric  argument is supplied, the output is formatted in such a way that it can be made part
              of an inputrc file.
       display-shell-version (C-x C-v)
              Display version information about the current instance of bash.

   Programmable Completion
       When word completion is attempted for an argument to a command for which a completion  specification
       (a  compspec)  has  been  defined using the complete builtin (see SHELL BUILTIN COMMANDS below), the
       programmable completion facilities are invoked.

       First, the command name is identified.  If the command word is  the  empty  string  (completion  at‐
       tempted  at  the beginning of an empty line), any compspec defined with the -E option to complete is
       used.  If a compspec has been defined for that command, the compspec is used to generate the list of
       possible  completions for the word.  If the command word is a full pathname, a compspec for the full
       pathname is searched for first.  If no compspec is found for the full pathname, an attempt  is  made
       to  find a compspec for the portion following the final slash.  If those searches do not result in a
       compspec, any compspec defined with the -D option to complete is used as the default.  If  there  is
       no  default  compspec,  bash attempts alias expansion on the command word as a final resort, and at‐
       tempts to find a compspec for the command word from any successful expansion.

       Once a compspec has been found, it is used to generate the list of matching words.  If a compspec is
       not found, the default bash completion as described above under Completing is performed.

       First,  the actions specified by the compspec are used.  Only matches which are prefixed by the word
       being completed are returned.  When the -f or -d option is used for filename or directory name  com‐
       pletion, the shell variable FIGNORE is used to filter the matches.

       Any  completions specified by a pathname expansion pattern to the -G option are generated next.  The
       words generated by the pattern need not match the word being completed.  The GLOBIGNORE shell  vari‐
       able is not used to filter the matches, but the FIGNORE variable is used.

       Next,  the  string  specified  as  the argument to the -W option is considered.  The string is first
       split using the characters in the IFS special variable as delimiters.   Shell  quoting  is  honored.
       Each word is then expanded using brace expansion, tilde expansion, parameter and variable expansion,
       command substitution, and arithmetic expansion, as described above under EXPANSION.  The results are
       split  using  the rules described above under Word Splitting.  The results of the expansion are pre‐
       fix-matched against the word being completed, and the matching words  become  the  possible  comple‐
       tions.

       After  these matches have been generated, any shell function or command specified with the -F and -C
       options is invoked.  When the command or function is invoked, the COMP_LINE,  COMP_POINT,  COMP_KEY,
       and  COMP_TYPE  variables  are assigned values as described above under Shell Variables.  If a shell
       function is being invoked, the COMP_WORDS and COMP_CWORD variables are also set.  When the  function
       or  command is invoked, the first argument ($1) is the name of the command whose arguments are being
       completed, the second argument ($2) is the word being completed, and the third argument ($3) is  the
       word  preceding the word being completed on the current command line.  No filtering of the generated
       completions against the word being completed is performed; the  function  or  command  has  complete
       freedom in generating the matches.

       Any  function specified with -F is invoked first.  The function may use any of the shell facilities,
       including the compgen builtin described below, to generate the matches.  It must  put  the  possible
       completions in the COMPREPLY array variable, one per array element.

       Next,  any  command  specified with the -C option is invoked in an environment equivalent to command
       substitution.  It should print a list of completions, one per line, to the standard  output.   Back‐
       slash may be used to escape a newline, if necessary.

       After  all of the possible completions are generated, any filter specified with the -X option is ap‐
       plied to the list.  The filter is a pattern as used for pathname expansion; a & in  the  pattern  is
       replaced  with  the  text of the word being completed.  A literal & may be escaped with a backslash;
       the backslash is removed before attempting a match.  Any completion that matches the pattern will be
       removed  from  the  list.  A leading ! negates the pattern; in this case any completion not matching
       the pattern will be removed.  If the nocasematch shell option is enabled,  the  match  is  performed
       without regard to the case of alphabetic characters.

       Finally,  any prefix and suffix specified with the -P and -S options are added to each member of the
       completion list, and the result is returned to the readline completion code as the list of  possible
       completions.

       If  the  previously-applied actions do not generate any matches, and the -o dirnames option was sup‐
       plied to complete when the compspec was defined, directory name completion is attempted.

       If the -o plusdirs option was supplied to complete when the compspec  was  defined,  directory  name
       completion is attempted and any matches are added to the results of the other actions.

       By  default, if a compspec is found, whatever it generates is returned to the completion code as the
       full set of possible completions.  The default bash completions are not attempted, and the  readline
       default  of  filename completion is disabled.  If the -o bashdefault option was supplied to complete
       when the compspec was defined, the bash default completions are attempted if the compspec  generates
       no  matches.  If the -o default option was supplied to complete when the compspec was defined, read‐
       line's default completion will be performed if the compspec (and, if  attempted,  the  default  bash
       completions) generate no matches.

       When  a  compspec  indicates  that directory name completion is desired, the programmable completion
       functions force readline to append a slash to completed names which are symbolic links  to  directo‐
       ries,  subject  to the value of the mark-directories readline variable, regardless of the setting of
       the mark-symlinked-directories readline variable.

       There is some support for dynamically modifying completions.  This is most useful when used in  com‐
       bination  with  a  default completion specified with complete -D.  It's possible for shell functions
       executed as completion handlers to indicate that completion should be retried by returning  an  exit
       status  of  124.  If a shell function returns 124, and changes the compspec associated with the com‐
       mand on which completion is being attempted (supplied as the first argument when the function is ex‐
       ecuted), programmable completion restarts from the beginning, with an attempt to find a new compspec
       for that command.  This allows a set of completions to be built dynamically  as  completion  is  at‐
       tempted, rather than being loaded all at once.

       For  instance,  assuming  that there is a library of compspecs, each kept in a file corresponding to
       the name of the command, the following default completion function would  load  completions  dynami‐
       cally:

       _completion_loader()
       {
            . "/etc/bash_completion.d/$1.sh" >/dev/null 2>&1 && return 124
       }
       complete -D -F _completion_loader -o bashdefault -o default

HISTORY
       When  the  -o history option to the set builtin is enabled, the shell provides access to the command
       history, the list of commands previously typed.  The value of the HISTSIZE variable is used  as  the
       number  of commands to save in a history list.  The text of the last HISTSIZE commands (default 500)
       is saved.  The shell stores each command in the history list prior to parameter and variable  expan‐
       sion  (see  EXPANSION  above) but after history expansion is performed, subject to the values of the
       shell variables HISTIGNORE and HISTCONTROL.

       On startup, the history is initialized from  the  file  named  by  the  variable  HISTFILE  (default
       ~/.bash_history).  The file named by the value of HISTFILE is truncated, if necessary, to contain no
       more than the number of lines specified by the value of HISTFILESIZE.  If HISTFILESIZE is unset,  or
       set  to  null, a non-numeric value, or a numeric value less than zero, the history file is not trun‐
       cated.  When the history file is read, lines beginning with the history comment  character  followed
       immediately  by  a  digit are interpreted as timestamps for the following history line.  These time‐
       stamps are optionally displayed depending on the value of the HISTTIMEFORMAT variable.  When a shell
       with  history enabled exits, the last $HISTSIZE lines are copied from the history list to $HISTFILE.
       If the histappend shell option is enabled (see the description of shopt under SHELL BUILTIN COMMANDS
       below),  the  lines are appended to the history file, otherwise the history file is overwritten.  If
       HISTFILE is unset, or if the history file is unwritable, the history is not saved.  If the HISTTIME‐
       FORMAT variable is set, time stamps are written to the history file, marked with the history comment
       character, so they may be preserved across shell sessions.  This uses the history comment  character
       to  distinguish  timestamps from other history lines.  After saving the history, the history file is
       truncated to contain no more than HISTFILESIZE lines.  If HISTFILESIZE is unset, or set to  null,  a
       non-numeric value, or a numeric value less than zero, the history file is not truncated.

       The builtin command fc (see SHELL BUILTIN COMMANDS below) may be used to list or edit and re-execute
       a portion of the history list.  The history builtin may be used to display  or  modify  the  history
       list  and  manipulate the history file.  When using command-line editing, search commands are avail‐
       able in each editing mode that provide access to the history list.

       The shell allows control over which commands are saved on the history  list.   The  HISTCONTROL  and
       HISTIGNORE  variables  may  be set to cause the shell to save only a subset of the commands entered.
       The cmdhist shell option, if enabled, causes the shell to attempt to save each line of a  multi-line
       command  in the same history entry, adding semicolons where necessary to preserve syntactic correct‐
       ness.  The lithist shell option causes the shell to save the command with embedded newlines  instead
       of  semicolons.  See the description of the shopt builtin below under SHELL BUILTIN COMMANDS for in‐
       formation on setting and unsetting shell options.

HISTORY EXPANSION
       The shell supports a history expansion feature that is similar to  the  history  expansion  in  csh.
       This  section  describes what syntax features are available.  This feature is enabled by default for
       interactive shells, and can be disabled using the +H option to the set builtin  command  (see  SHELL
       BUILTIN COMMANDS below).  Non-interactive shells do not perform history expansion by default.

       History  expansions  introduce  words from the history list into the input stream, making it easy to
       repeat commands, insert the arguments to a previous command into the current input line, or fix  er‐
       rors in previous commands quickly.

       History expansion is performed immediately after a complete line is read, before the shell breaks it
       into words, and is performed on each line individually without taking quoting on previous lines into
       account.   It  takes place in two parts.  The first is to determine which line from the history list
       to use during substitution.  The second is to select portions of that line for  inclusion  into  the
       current  one.   The  line selected from the history is the event, and the portions of that line that
       are acted upon are words.  Various modifiers are available to manipulate the  selected  words.   The
       line  is broken into words in the same fashion as when reading input, so that several metacharacter-
       separated words surrounded by quotes are considered one word.  History expansions are introduced  by
       the  appearance  of  the history expansion character, which is ! by default.  Only backslash (\) and
       single quotes can quote the history expansion character, but the history expansion character is also
       treated as quoted if it immediately precedes the closing double quote in a double-quoted string.

       Several  characters  inhibit  history expansion if found immediately following the history expansion
       character, even if it is unquoted: space, tab, newline, carriage return,  and  =.   If  the  extglob
       shell option is enabled, ( will also inhibit expansion.

       Several  shell options settable with the shopt builtin may be used to tailor the behavior of history
       expansion.  If the histverify shell option is enabled (see the description of the shopt builtin  be‐
       low),  and  readline  is  being  used, history substitutions are not immediately passed to the shell
       parser.  Instead, the expanded line is reloaded into the readline editing buffer for further modifi‐
       cation.   If  readline  is  being used, and the histreedit shell option is enabled, a failed history
       substitution will be reloaded into the readline editing buffer for correction.  The -p option to the
       history builtin command may be used to see what a history expansion will do before using it.  The -s
       option to the history builtin may be used to add commands to the end of the history list without ac‐
       tually executing them, so that they are available for subsequent recall.

       The  shell allows control of the various characters used by the history expansion mechanism (see the
       description of histchars above under Shell Variables).  The shell uses the history comment character
       to mark history timestamps when writing the history file.

   Event Designators
       An  event  designator is a reference to a command line entry in the history list.  Unless the refer‐
       ence is absolute, events are relative to the current position in the history list.

       !      Start a history substitution, except when followed by a blank, newline, carriage return, = or
              ( (when the extglob shell option is enabled using the shopt builtin).
       !n     Refer to command line n.
       !-n    Refer to the current command minus n.
       !!     Refer to the previous command.  This is a synonym for `!-1'.
       !string
              Refer  to the most recent command preceding the current position in the history list starting
              with string.
       !?string[?]
              Refer to the most recent command preceding the current position in the history list  contain‐
              ing  string.   The  trailing ? may be omitted if string is followed immediately by a newline.
              If string is missing, the string from the most recent search is used; it is an error if there
              is no previous search string.
       ^string1^string2^
              Quick substitution.  Repeat the previous command, replacing string1 with string2.  Equivalent
              to ``!!:s^string1^string2^'' (see Modifiers below).
       !#     The entire command line typed so far.

   Word Designators
       Word designators are used to select desired words from the event.  A : separates the event  specifi‐
       cation from the word designator.  It may be omitted if the word designator begins with a ^, $, *, -,
       or %.  Words are numbered from the beginning of the line, with the first word  being  denoted  by  0
       (zero).  Words are inserted into the current line separated by single spaces.

       0 (zero)
              The zeroth word.  For the shell, this is the command word.
       n      The nth word.
       ^      The first argument.  That is, word 1.
       $      The  last  word.   This  is  usually the last argument, but will expand to the zeroth word if
              there is only one word in the line.
       %      The first word matched by the most recent `?string?' search, if the search string begins with
              a character that is part of a word.
       x-y    A range of words; `-y' abbreviates `0-y'.
       *      All  of  the words but the zeroth.  This is a synonym for `1-$'.  It is not an error to use *
              if there is just one word in the event; the empty string is returned in that case.
       x*     Abbreviates x-$.
       x-     Abbreviates x-$ like x*, but omits the last word.  If x is missing, it defaults to 0.

       If a word designator is supplied without an event specification, the previous command is used as the
       event.

   Modifiers
       After the optional word designator, there may appear a sequence of one or more of the following mod‐
       ifiers, each preceded by a `:'.  These modify, or edit, the word or words selected from the  history
       event.

       h      Remove a trailing filename component, leaving only the head.
       t      Remove all leading filename components, leaving the tail.
       r      Remove a trailing suffix of the form .xxx, leaving the basename.
       e      Remove all but the trailing suffix.
       p      Print the new command but do not execute it.
       q      Quote the substituted words, escaping further substitutions.
       x      Quote  the  substituted  words as with q, but break into words at blanks and newlines.  The q
              and x modifiers are mutually exclusive; the last one supplied is used.
       s/old/new/
              Substitute new for the first occurrence of old in the event line.  Any character may be  used
              as  the delimiter in place of /.  The final delimiter is optional if it is the last character
              of the event line.  The delimiter may be quoted in old and new with a single backslash.  If &
              appears in new, it is replaced by old.  A single backslash will quote the &.  If old is null,
              it is set to the last old substituted, or, if no previous history substitutions  took  place,
              the last string in a !?string[?]  search.  If new is null, each matching old is deleted.
       &      Repeat the previous substitution.
       g      Cause  changes  to  be  applied over the entire event line.  This is used in conjunction with
              `:s' (e.g., `:gs/old/new/') or `:&'.  If used with `:s', any delimiter can be used  in  place
              of  /, and the final delimiter is optional if it is the last character of the event line.  An
              a may be used as a synonym for g.
       G      Apply the following `s' or `&' modifier once to each word in the event line.

SHELL BUILTIN COMMANDS
       Unless otherwise noted, each builtin command documented in this section as  accepting  options  pre‐
       ceded by - accepts -- to signify the end of the options.  The :, true, false, and test/[ builtins do
       not accept options and do not treat -- specially.  The exit, logout, return, break,  continue,  let,
       and  shift  builtins  accept  and  process  arguments  beginning with - without requiring --.  Other
       builtins that accept arguments but are not specified as accepting options interpret arguments begin‐
       ning with - as invalid options and require -- to prevent this interpretation.
       : [arguments]
              No  effect;  the command does nothing beyond expanding arguments and performing any specified
              redirections.  The return status is zero.

        .  filename [arguments]
       source filename [arguments]
              Read and execute commands from filename in the current shell environment and return the  exit
              status  of  the  last  command executed from filename.  If filename does not contain a slash,
              filenames in PATH are used to find the directory containing filename, but filename  does  not
              need  to  be executable.  The file searched for in PATH need not be executable.  When bash is
              not in posix mode, it searches the current directory if no file is found  in  PATH.   If  the
              sourcepath  option  to the shopt builtin command is turned off, the PATH is not searched.  If
              any arguments are supplied, they become the positional parameters when filename is  executed.
              Otherwise  the  positional parameters are unchanged.  If the -T option is enabled, . inherits
              any trap on DEBUG; if it is not, any DEBUG trap string is saved and restored around the  call
              to  ., and . unsets the DEBUG trap while it executes.  If -T is not set, and the sourced file
              changes the DEBUG trap, the new value is retained when . completes.  The return status is the
              status  of  the  last  command  exited within the script (0 if no commands are executed), and
              false if filename is not found or cannot be read.

       alias [-p] [name[=value] ...]
              Alias with no arguments or with the -p option prints the list of aliases in  the  form  alias
              name=value  on  standard  output.   When arguments are supplied, an alias is defined for each
              name whose value is given.  A trailing space in value causes the next word to be checked  for
              alias  substitution when the alias is expanded.  For each name in the argument list for which
              no value is supplied, the name and value of the alias is printed.  Alias returns true  unless
              a name is given for which no alias has been defined.

       bg [jobspec ...]
              Resume  each  suspended  job jobspec in the background, as if it had been started with &.  If
              jobspec is not present, the shell's notion of the current job is used.  bg jobspec returns  0
              unless  run when job control is disabled or, when run with job control enabled, any specified
              jobspec was not found or was started without job control.

       bind [-m keymap] [-lpsvPSVX]
       bind [-m keymap] [-q function] [-u function] [-r keyseq]
       bind [-m keymap] -f filename
       bind [-m keymap] -x keyseq:shell-command
       bind [-m keymap] keyseq:function-name
       bind [-m keymap] keyseq:readline-command
       bind readline-command-line
              Display current readline key and function bindings, bind a key sequence to a  readline  func‐
              tion or macro, or set a readline variable.  Each non-option argument is a command as it would
              appear in a readline initialization file such as .inputrc, but each binding or  command  must
              be  passed  as  a separate argument; e.g., '"\C-x\C-r": re-read-init-file'.  Options, if sup‐
              plied, have the following meanings:
              -m keymap
                     Use keymap as the keymap to be affected by the subsequent bindings.  Acceptable keymap
                     names  are emacs, emacs-standard, emacs-meta, emacs-ctlx, vi, vi-move, vi-command, and
                     vi-insert.  vi is equivalent to vi-command (vi-move  is  also  a  synonym);  emacs  is
                     equivalent to emacs-standard.
              -l     List the names of all readline functions.
              -p     Display readline function names and bindings in such a way that they can be re-read.
              -P     List current readline function names and bindings.
              -s     Display  readline  key sequences bound to macros and the strings they output in such a
                     way that they can be re-read.
              -S     Display readline key sequences bound to macros and the strings they output.
              -v     Display readline variable names and values in such a way that they can be re-read.
              -V     List current readline variable names and values.
              -f filename
                     Read key bindings from filename.
              -q function
                     Query about which keys invoke the named function.
              -u function
                     Unbind all keys bound to the named function.
              -r keyseq
                     Remove any current binding for keyseq.
              -x keyseq:shell-command
                     Cause shell-command to be executed whenever keyseq is entered.  When shell-command  is
                     executed,  the  shell  sets the READLINE_LINE variable to the contents of the readline
                     line buffer and the READLINE_POINT and READLINE_MARK variables to the current location
                     of  the  insertion  point and the saved insertion point (the mark), respectively.  The
                     shell assigns any numeric argument the user supplied to  the  READLINE_ARGUMENT  vari‐
                     able.   If  there  was no argument, that variable is not set.  If the executed command
                     changes the value of any of READLINE_LINE, READLINE_POINT, or READLINE_MARK, those new
                     values will be reflected in the editing state.
              -X     List all key sequences bound to shell commands and the associated commands in a format
                     that can be reused as input.

              The return value is 0 unless an unrecognized option is given or an error occurred.

       break [n]
              Exit from within a for, while, until, or select loop.  If n is specified, break n levels.   n
              must be ≥ 1.  If n is greater than the number of enclosing loops, all enclosing loops are ex‐
              ited.  The return value is 0 unless n is not greater than or equal to 1.

       builtin shell-builtin [arguments]
              Execute the specified shell builtin, passing it arguments, and return its exit status.   This
              is  useful  when defining a function whose name is the same as a shell builtin, retaining the
              functionality of the builtin within the function.  The cd builtin is commonly redefined  this
              way.  The return status is false if shell-builtin is not a shell builtin command.

       caller [expr]
              Returns the context of any active subroutine call (a shell function or a script executed with
              the . or source builtins).  Without expr, caller displays the line number and source filename
              of  the  current subroutine call.  If a non-negative integer is supplied as expr, caller dis‐
              plays the line number, subroutine name, and source file corresponding to that position in the
              current  execution  call  stack.  This extra information may be used, for example, to print a
              stack trace.  The current frame is frame 0.  The return value is 0 unless the  shell  is  not
              executing  a  subroutine  call  or  expr  does not correspond to a valid position in the call
              stack.

       cd [-L|[-P [-e]] [-@]] [dir]
              Change the current directory to dir.  if dir is not supplied, the value  of  the  HOME  shell
              variable  is the default.  The variable CDPATH defines the search path for the directory con‐
              taining dir: each directory name in CDPATH is searched for dir.  Alternative directory  names
              in  CDPATH  are separated by a colon (:).  A null directory name in CDPATH is the same as the
              current directory, i.e., ``.''.  If dir begins with a slash (/), then  CDPATH  is  not  used.
              The  -P  option causes cd to use the physical directory structure by resolving symbolic links
              while traversing dir and before processing instances of .. in dir (see also the -P option  to
              the set builtin command); the -L option forces symbolic links to be followed by resolving the
              link after processing instances of .. in dir.  If .. appears in dir, it is processed  by  re‐
              moving the immediately previous pathname component from dir, back to a slash or the beginning
              of dir.  If the -e option is supplied with -P, and the current working  directory  cannot  be
              successfully  determined  after a successful directory change, cd will return an unsuccessful
              status.  On systems that support it, the -@ option presents the extended  attributes  associ‐
              ated  with a file as a directory.  An argument of - is converted to $OLDPWD before the direc‐
              tory change is attempted.  If a non-empty directory name from CDPATH is used, or if - is  the
              first  argument,  and  the  directory  change is successful, the absolute pathname of the new
              working directory is written to the standard output.  If the directory change is  successful,
              cd  sets  the  value  of the PWD environment variable to the new directory name, and sets the
              OLDPWD environment variable to the value of the current working directory before the  change.
              The return value is true if the directory was successfully changed; false otherwise.

       command [-pVv] command [arg ...]
              Run command with args suppressing the normal shell function lookup.  Only builtin commands or
              commands found in the PATH are executed.  If the -p option is given, the search  for  command
              is  performed  using  a default value for PATH that is guaranteed to find all of the standard
              utilities.  If either the -V or -v option is supplied, a description of command  is  printed.
              The  -v option causes a single word indicating the command or filename used to invoke command
              to be displayed; the -V option produces a more verbose description.  If the -V or  -v  option
              is  supplied,  the exit status is 0 if command was found, and 1 if not.  If neither option is
              supplied and an error occurred or command cannot be found, the exit status  is  127.   Other‐
              wise, the exit status of the command builtin is the exit status of command.

       compgen [option] [word]
              Generate  possible completion matches for word according to the options, which may be any op‐
              tion accepted by the complete builtin with the exception of -p and -r, and write the  matches
              to  the standard output.  When using the -F or -C options, the various shell variables set by
              the programmable completion facilities, while available, will not have useful values.

              The matches will be generated in the same way as if the programmable completion code had gen‐
              erated  them directly from a completion specification with the same flags.  If word is speci‐
              fied, only those completions matching word will be displayed.

              The return value is true unless an invalid option is supplied, or no matches were generated.

       complete [-abcdefgjksuv] [-o comp-option] [-DEI] [-A action] [-G globpat] [-W wordlist]
              [-F function] [-C command] [-X filterpat] [-P prefix] [-S suffix] name [name ...]
       complete -pr [-DEI] [name ...]
              Specify how arguments to each name should be completed.  If the -p option is supplied, or  if
              no  options are supplied, existing completion specifications are printed in a way that allows
              them to be reused as input.  The -r option removes a completion specification for each  name,
              or,  if  no  names are supplied, all completion specifications.  The -D option indicates that
              other supplied options and actions should apply to the ``default'' command  completion;  that
              is,  completion  attempted  on a command for which no completion has previously been defined.
              The -E option indicates that other supplied options and actions  should  apply  to  ``empty''
              command  completion;  that is, completion attempted on a blank line.  The -I option indicates
              that other supplied options and actions should apply to completion on the initial non-assign‐
              ment  word on the line, or after a command delimiter such as ; or |, which is usually command
              name completion.  If multiple options are supplied, the -D option takes precedence  over  -E,
              and both take precedence over -I.  If any of -D, -E, or -I are supplied, any other name argu‐
              ments are ignored; these completions only apply to the case specified by the option.

              The process of applying these completion specifications when word completion is attempted  is
              described above under Programmable Completion.

              Other  options,  if specified, have the following meanings.  The arguments to the -G, -W, and
              -X options (and, if necessary, the -P and -S options) should be quoted to protect  them  from
              expansion before the complete builtin is invoked.
              -o comp-option
                      The comp-option controls several aspects of the compspec's behavior beyond the simple
                      generation of completions.  comp-option may be one of:
                      bashdefault
                              Perform the rest of the default bash completions if the compspec generates no
                              matches.
                      default Use  readline's  default  filename  completion  if  the compspec generates no
                              matches.
                      dirnames
                              Perform directory name completion if the compspec generates no matches.
                      filenames
                              Tell readline that the compspec generates filenames, so it  can  perform  any
                              filename-specific processing (like adding a slash to directory names, quoting
                              special characters, or suppressing trailing spaces).   Intended  to  be  used
                              with shell functions.
                      noquote Tell readline not to quote the completed words if they are filenames (quoting
                              filenames is the default).
                      nosort  Tell readline not to sort the list of possible completions alphabetically.
                      nospace Tell readline not to append a space (the default) to words completed  at  the
                              end of the line.
                      plusdirs
                              After  any matches defined by the compspec are generated, directory name com‐
                              pletion is attempted and any matches are added to the results  of  the  other
                              actions.
              -A action
                      The action may be one of the following to generate a list of possible completions:
                      alias   Alias names.  May also be specified as -a.
                      arrayvar
                              Array variable names.
                      binding Readline key binding names.
                      builtin Names of shell builtin commands.  May also be specified as -b.
                      command Command names.  May also be specified as -c.
                      directory
                              Directory names.  May also be specified as -d.
                      disabled
                              Names of disabled shell builtins.
                      enabled Names of enabled shell builtins.
                      export  Names of exported shell variables.  May also be specified as -e.
                      file    File names.  May also be specified as -f.
                      function
                              Names of shell functions.
                      group   Group names.  May also be specified as -g.
                      helptopic
                              Help topics as accepted by the help builtin.
                      hostname
                              Hostnames, as taken from the file specified by the HOSTFILE shell variable.
                      job     Job names, if job control is active.  May also be specified as -j.
                      keyword Shell reserved words.  May also be specified as -k.
                      running Names of running jobs, if job control is active.
                      service Service names.  May also be specified as -s.
                      setopt  Valid arguments for the -o option to the set builtin.
                      shopt   Shell option names as accepted by the shopt builtin.
                      signal  Signal names.
                      stopped Names of stopped jobs, if job control is active.
                      user    User names.  May also be specified as -u.
                      variable
                              Names of all shell variables.  May also be specified as -v.
              -C command
                      command is executed in a subshell environment, and its output is used as the possible
                      completions.  Arguments are passed as with the -F option.
              -F function
                      The shell function function is executed in the current shell environment.   When  the
                      function  is executed, the first argument ($1) is the name of the command whose argu‐
                      ments are being completed, the second argument ($2) is the word being completed,  and
                      the third argument ($3) is the word preceding the word being completed on the current
                      command line.  When it finishes, the possible  completions  are  retrieved  from  the
                      value of the COMPREPLY array variable.
              -G globpat
                      The  pathname  expansion pattern globpat is expanded to generate the possible comple‐
                      tions.
              -P prefix
                      prefix is added at the beginning of each possible completion after all other  options
                      have been applied.
              -S suffix
                      suffix  is appended to each possible completion after all other options have been ap‐
                      plied.
              -W wordlist
                      The wordlist is split using the characters in the IFS special variable as delimiters,
                      and  each  resultant  word is expanded.  Shell quoting is honored within wordlist, in
                      order to provide a mechanism for the words to contain shell metacharacters or charac‐
                      ters  in the value of IFS.  The possible completions are the members of the resultant
                      list which match the word being completed.
              -X filterpat
                      filterpat is a pattern as used for pathname expansion.  It is applied to the list  of
                      possible  completions generated by the preceding options and arguments, and each com‐
                      pletion matching filterpat is removed from  the  list.   A  leading  !  in  filterpat
                      negates the pattern; in this case, any completion not matching filterpat is removed.

              The  return value is true unless an invalid option is supplied, an option other than -p or -r
              is supplied without a name argument, an attempt is made to remove a completion  specification
              for a name for which no specification exists, or an error occurs adding a completion specifi‐
              cation.

       compopt [-o option] [-DEI] [+o option] [name]
              Modify completion options for each name according to the options, or for  the  currently-exe‐
              cuting  completion if no names are supplied.  If no options are given, display the completion
              options for each name or the current completion.  The possible values  of  option  are  those
              valid  for the complete builtin described above.  The -D option indicates that other supplied
              options should apply to the ``default'' command completion; that is, completion attempted  on
              a  command for which no completion has previously been defined.  The -E option indicates that
              other supplied options should apply to ``empty'' command completion; that is, completion  at‐
              tempted on a blank line.  The -I option indicates that other supplied options should apply to
              completion on the initial non-assignment word on the line, or after a command delimiter  such
              as ; or |, which is usually command name completion.

              The  return  value is true unless an invalid option is supplied, an attempt is made to modify
              the options for a name for which no completion specification exists, or an output  error  oc‐
              curs.

       continue [n]
              Resume the next iteration of the enclosing for, while, until, or select loop.  If n is speci‐
              fied, resume at the nth enclosing loop.  n must be ≥ 1.  If n is greater than the  number  of
              enclosing  loops,  the  last  enclosing loop (the ``top-level'' loop) is resumed.  The return
              value is 0 unless n is not greater than or equal to 1.

       declare [-aAfFgiIlnrtux] [-p] [name[=value] ...]
       typeset [-aAfFgiIlnrtux] [-p] [name[=value] ...]
              Declare variables and/or give them attributes.  If no names are given then display the values
              of variables.  The -p option will display the attributes and values of each name.  When -p is
              used with name arguments, additional options, other than -f and -F, are ignored.  When -p  is
              supplied  without  name arguments, it will display the attributes and values of all variables
              having the attributes specified by the additional options.  If no other options are  supplied
              with  -p,  declare will display the attributes and values of all shell variables.  The -f op‐
              tion will restrict the display to shell functions.  The -F option  inhibits  the  display  of
              function  definitions;  only  the  function name and attributes are printed.  If the extdebug
              shell option is enabled using shopt, the source file name and line number where each name  is
              defined  are displayed as well.  The -F option implies -f.  The -g option forces variables to
              be created or modified at the global scope, even when declare is executed in  a  shell  func‐
              tion.  It is ignored in all other cases.  The -I option causes local variables to inherit the
              attributes (except the nameref attribute) and value of any existing variable  with  the  same
              name  at  a  surrounding scope.  If there is no existing variable, the local variable is ini‐
              tially unset.  The following options can be used to restrict output  to  variables  with  the
              specified attribute or to give variables attributes:
              -a     Each name is an indexed array variable (see Arrays above).
              -A     Each name is an associative array variable (see Arrays above).
              -f     Use function names only.
              -i     The  variable  is treated as an integer; arithmetic evaluation (see ARITHMETIC EVALUA‐
                     TION above) is performed when the variable is assigned a value.
              -l     When the variable is assigned a value, all  upper-case  characters  are  converted  to
                     lower-case.  The upper-case attribute is disabled.
              -n     Give  each name the nameref attribute, making it a name reference to another variable.
                     That other variable is defined by the value of name.  All references, assignments, and
                     attribute  modifications  to name, except those using or changing the -n attribute it‐
                     self, are performed on the variable referenced by name's value.  The nameref attribute
                     cannot be applied to array variables.
              -r     Make names readonly.  These names cannot then be assigned values by subsequent assign‐
                     ment statements or unset.
              -t     Give each name the trace attribute.  Traced functions inherit  the  DEBUG  and  RETURN
                     traps  from  the  calling shell.  The trace attribute has no special meaning for vari‐
                     ables.
              -u     When the variable is assigned a value, all lower-case characters are converted to  up‐
                     per-case.  The lower-case attribute is disabled.
              -x     Mark names for export to subsequent commands via the environment.

              Using  `+' instead of `-' turns off the attribute instead, with the exceptions that +a and +A
              may not be used to destroy array variables and +r will not  remove  the  readonly  attribute.
              When used in a function, declare and typeset make each name local, as with the local command,
              unless the -g option is supplied.  If a variable name is followed by =value, the value of the
              variable  is  set to value.  When using -a or -A and the compound assignment syntax to create
              array variables, additional attributes do not take effect until subsequent assignments.   The
              return  value  is  0  unless an invalid option is encountered, an attempt is made to define a
              function using ``-f foo=bar'', an attempt is made to assign a value to a  readonly  variable,
              an  attempt is made to assign a value to an array variable without using the compound assign‐
              ment syntax (see Arrays above), one of the names is not a valid shell variable name,  an  at‐
              tempt is made to turn off readonly status for a readonly variable, an attempt is made to turn
              off array status for an array variable, or an attempt is made to display a non-existent func‐
              tion with -f.

       dirs [-clpv] [+n] [-n]
              Without  options, displays the list of currently remembered directories.  The default display
              is on a single line with directory names separated by spaces.  Directories are added  to  the
              list with the pushd command; the popd command removes entries from the list.  The current di‐
              rectory is always the first directory in the stack.
              -c     Clears the directory stack by deleting all of the entries.
              -l     Produces a listing using full pathnames; the default listing format uses  a  tilde  to
                     denote the home directory.
              -p     Print the directory stack with one entry per line.
              -v     Print the directory stack with one entry per line, prefixing each entry with its index
                     in the stack.
              +n     Displays the nth entry counting from the left of the list shown by dirs  when  invoked
                     without options, starting with zero.
              -n     Displays  the nth entry counting from the right of the list shown by dirs when invoked
                     without options, starting with zero.

              The return value is 0 unless an invalid option is supplied or n indexes beyond the end of the
              directory stack.

       disown [-ar] [-h] [jobspec ... | pid ... ]
              Without  options,  remove  each  jobspec  from  the  table of active jobs.  If jobspec is not
              present, and neither the -a nor the -r option is supplied, the current job is used.   If  the
              -h  option is given, each jobspec is not removed from the table, but is marked so that SIGHUP
              is not sent to the job if the shell receives a SIGHUP.  If no jobspec is supplied, the -a op‐
              tion means to remove or mark all jobs; the -r option without a jobspec argument restricts op‐
              eration to running jobs.  The return value is 0 unless a jobspec does  not  specify  a  valid
              job.

       echo [-neE] [arg ...]
              Output the args, separated by spaces, followed by a newline.  The return status is 0 unless a
              write error occurs.  If -n is specified, the trailing newline is suppressed.  If the  -e  op‐
              tion  is given, interpretation of the following backslash-escaped characters is enabled.  The
              -E option disables the interpretation of these escape characters, even on systems where  they
              are  interpreted  by default.  The xpg_echo shell option may be used to dynamically determine
              whether or not echo expands these escape characters by default.  echo does not  interpret  --
              to mean the end of options.  echo interprets the following escape sequences:
              \a     alert (bell)
              \b     backspace
              \c     suppress further output
              \e
              \E     an escape character
              \f     form feed
              \n     new line
              \r     carriage return
              \t     horizontal tab
              \v     vertical tab
              \\     backslash
              \0nnn  the  eight-bit  character whose value is the octal value nnn (zero to three octal dig‐
                     its)
              \xHH   the eight-bit character whose value is the hexadecimal value HH (one or two  hex  dig‐
                     its)
              \uHHHH the  Unicode  (ISO/IEC 10646) character whose value is the hexadecimal value HHHH (one
                     to four hex digits)
              \UHHHHHHHH
                     the Unicode (ISO/IEC 10646) character whose value is the  hexadecimal  value  HHHHHHHH
                     (one to eight hex digits)

       enable [-a] [-dnps] [-f filename] [name ...]
              Enable  and  disable builtin shell commands.  Disabling a builtin allows a disk command which
              has the same name as a shell builtin to be executed without specifying a full pathname,  even
              though  the  shell  normally searches for builtins before disk commands.  If -n is used, each
              name is disabled; otherwise, names are enabled.  For example, to use the  test  binary  found
              via  the  PATH  instead  of the shell builtin version, run ``enable -n test''.  The -f option
              means to load the new builtin command name from shared object filename, on systems that  sup‐
              port  dynamic  loading.   Bash  will  use  the value of the BASH_LOADABLES_PATH variable as a
              colon-separated list of directories in which to search for filename.  The default is  system-
              dependent.   The -d option will delete a builtin previously loaded with -f.  If no name argu‐
              ments are given, or if the -p option is supplied, a list of shell builtins is printed.   With
              no  other  option  arguments, the list consists of all enabled shell builtins.  If -n is sup‐
              plied, only disabled builtins are printed.  If -a is supplied, the list printed includes  all
              builtins,  with an indication of whether or not each is enabled.  If -s is supplied, the out‐
              put is restricted to the POSIX special builtins.  If no options are supplied and  a  name  is
              not  a shell builtin, enable will attempt to load name from a shared object named name, as if
              the command were ``enable -f name name .  The return value is 0 unless a name is not a  shell
              builtin or there is an error loading a new builtin from a shared object.

       eval [arg ...]
              The args are read and concatenated together into a single command.  This command is then read
              and executed by the shell, and its exit status is returned as the value of  eval.   If  there
              are no args, or only null arguments, eval returns 0.

       exec [-cl] [-a name] [command [arguments]]
              If  command  is  specified, it replaces the shell.  No new process is created.  The arguments
              become the arguments to command.  If the -l option is supplied, the shell places  a  dash  at
              the  beginning of the zeroth argument passed to command.  This is what login(1) does.  The -c
              option causes command to be executed with an empty environment.  If -a is supplied, the shell
              passes  name  as  the zeroth argument to the executed command.  If command cannot be executed
              for some reason, a non-interactive shell exits, unless the execfail shell option is  enabled.
              In that case, it returns failure.  An interactive shell returns failure if the file cannot be
              executed.  A subshell exits unconditionally if exec fails.  If command is not specified,  any
              redirections take effect in the current shell, and the return status is 0.  If there is a re‐
              direction error, the return status is 1.

       exit [n]
              Cause the shell to exit with a status of n.  If n is omitted, the exit status is that of  the
              last command executed.  A trap on EXIT is executed before the shell terminates.

       export [-fn] [name[=word]] ...
       export -p
              The  supplied  names  are marked for automatic export to the environment of subsequently exe‐
              cuted commands.  If the -f option is given, the names refer to functions.  If  no  names  are
              given, or if the -p option is supplied, a list of names of all exported variables is printed.
              The -n option causes the export property to be removed from each name.  If a variable name is
              followed  by  =word, the value of the variable is set to word.  export returns an exit status
              of 0 unless an invalid option is encountered, one of the names is not a valid shell  variable
              name, or -f is supplied with a name that is not a function.

       fc [-e ename] [-lnr] [first] [last]
       fc -s [pat=rep] [cmd]
              The  first form selects a range of commands from first to last from the history list and dis‐
              plays or edits and re-executes them.  First and last may be specified as a string (to  locate
              the  last command beginning with that string) or as a number (an index into the history list,
              where a negative number is used as an offset from the current command number).  When listing,
              a first or last of 0 is equivalent to -1 and -0 is equivalent to the current command (usually
              the fc command); otherwise 0 is equivalent to -1 and -0 is invalid.  If last  is  not  speci‐
              fied,  it is set to the current command for listing (so that ``fc -l -10'' prints the last 10
              commands) and to first otherwise.  If first is not specified, it is set to the previous  com‐
              mand for editing and -16 for listing.

              The  -n option suppresses the command numbers when listing.  The -r option reverses the order
              of the commands.  If the -l option is given, the commands  are  listed  on  standard  output.
              Otherwise,  the  editor  given  by  ename is invoked on a file containing those commands.  If
              ename is not given, the value of the FCEDIT variable is used, and  the  value  of  EDITOR  if
              FCEDIT  is  not  set.  If neither variable is set, vi is used.  When editing is complete, the
              edited commands are echoed and executed.

              In the second form, command is re-executed after each instance of pat  is  replaced  by  rep.
              Command  is  interpreted the same as first above.  A useful alias to use with this is ``r="fc
              -s"'', so that typing ``r cc'' runs the last command beginning with ``cc'' and  typing  ``r''
              re-executes the last command.

              If  the  first form is used, the return value is 0 unless an invalid option is encountered or
              first or last specify history lines out of range.  If the -e option is supplied,  the  return
              value is the value of the last command executed or failure if an error occurs with the tempo‐
              rary file of commands.  If the second form is used, the return status is that of the  command
              re-executed, unless cmd does not specify a valid history line, in which case fc returns fail‐
              ure.

       fg [jobspec]
              Resume jobspec in the foreground, and make it the current job.  If jobspec  is  not  present,
              the  shell's  notion  of  the  current  job is used.  The return value is that of the command
              placed into the foreground, or failure if run when job control is disabled or, when run  with
              job  control enabled, if jobspec does not specify a valid job or jobspec specifies a job that
              was started without job control.

       getopts optstring name [arg ...]
              getopts is used by shell procedures to parse positional parameters.  optstring  contains  the
              option  characters to be recognized; if a character is followed by a colon, the option is ex‐
              pected to have an argument, which should be separated from it by white space.  The colon  and
              question  mark  characters  may  not  be used as option characters.  Each time it is invoked,
              getopts places the next option in the shell variable name, initializing name if it  does  not
              exist,  and  the index of the next argument to be processed into the variable OPTIND.  OPTIND
              is initialized to 1 each time the shell or a shell script is invoked.   When  an  option  re‐
              quires  an  argument,  getopts places that argument into the variable OPTARG.  The shell does
              not reset OPTIND automatically; it must be manually reset between multiple calls  to  getopts
              within the same shell invocation if a new set of parameters is to be used.

              When  the end of options is encountered, getopts exits with a return value greater than zero.
              OPTIND is set to the index of the first non-option argument, and name is set to ?.

              getopts normally parses the positional parameters, but if more arguments are supplied as  arg
              values, getopts parses those instead.

              getopts  can  report  errors  in  two  ways.  If the first character of optstring is a colon,
              silent error reporting is used.  In normal operation, diagnostic messages  are  printed  when
              invalid  options  or missing option arguments are encountered.  If the variable OPTERR is set
              to 0, no error messages will be displayed, even if the first character of optstring is not  a
              colon.

              If  an invalid option is seen, getopts places ? into name and, if not silent, prints an error
              message and unsets OPTARG.  If getopts is silent, the option character found is placed in OP‐
              TARG and no diagnostic message is printed.

              If a required argument is not found, and getopts is not silent, a question mark (?) is placed
              in name, OPTARG is unset, and a diagnostic message is printed.  If getopts is silent, then  a
              colon (:) is placed in name and OPTARG is set to the option character found.

              getopts  returns  true if an option, specified or unspecified, is found.  It returns false if
              the end of options is encountered or an error occurs.

       hash [-lr] [-p filename] [-dt] [name]
              Each time hash is invoked, the full pathname of the command name is determined  by  searching
              the  directories  in  $PATH and remembered.  Any previously-remembered pathname is discarded.
              If the -p option is supplied, no path search is performed, and filename is used as  the  full
              filename  of the command.  The -r option causes the shell to forget all remembered locations.
              The -d option causes the shell to forget the remembered location of each name.  If the -t op‐
              tion  is  supplied, the full pathname to which each name corresponds is printed.  If multiple
              name arguments are supplied with -t, the name is printed before  the  hashed  full  pathname.
              The  -l  option causes output to be displayed in a format that may be reused as input.  If no
              arguments are given, or if only -l is supplied,  information  about  remembered  commands  is
              printed.   The  return status is true unless a name is not found or an invalid option is sup‐
              plied.

       help [-dms] [pattern]
              Display helpful information about builtin commands.  If pattern is specified, help gives  de‐
              tailed  help  on all commands matching pattern; otherwise help for all the builtins and shell
              control structures is printed.
              -d     Display a short description of each pattern
              -m     Display the description of each pattern in a manpage-like format
              -s     Display only a short usage synopsis for each pattern

              The return status is 0 unless no command matches pattern.

       history [n]
       history -c
       history -d offset
       history -d start-end
       history -anrw [filename]
       history -p arg [arg ...]
       history -s arg [arg ...]
              With no options, display the command history list with line numbers.  Lines listed with  a  *
              have  been  modified.   An  argument of n lists only the last n lines.  If the shell variable
              HISTTIMEFORMAT is set and not null, it is used as a format string for strftime(3) to  display
              the time stamp associated with each displayed history entry.  No intervening blank is printed
              between the formatted time stamp and the history line.  If filename is supplied, it  is  used
              as  the  name  of  the history file; if not, the value of HISTFILE is used.  Options, if sup‐
              plied, have the following meanings:
              -c     Clear the history list by deleting all the entries.
              -d offset
                     Delete the history entry at position offset.  If offset is negative, it is interpreted
                     as  relative  to one greater than the last history position, so negative indices count
                     back from the end of the history, and an index of -1 refers to the current history  -d
                     command.
              -d start-end
                     Delete the range of history entries between positions start and end, inclusive.  Posi‐
                     tive and negative values for start and end are interpreted as described above.
              -a     Append the ``new'' history lines to the history file.  These are history lines entered
                     since  the beginning of the current bash session, but not already appended to the his‐
                     tory file.
              -n     Read the history lines not already read from the history file into the current history
                     list.  These are lines appended to the history file since the beginning of the current
                     bash session.
              -r     Read the contents of the history file and append them to the current history list.
              -w     Write the current history list to the history file,  overwriting  the  history  file's
                     contents.
              -p     Perform history substitution on the following args and display the result on the stan‐
                     dard output.  Does not store the results in the history list.  Each arg must be quoted
                     to disable normal history expansion.
              -s     Store the args in the history list as a single entry.  The last command in the history
                     list is removed before the args are added.

              If the HISTTIMEFORMAT variable is set, the time stamp information associated with  each  his‐
              tory  entry  is written to the history file, marked with the history comment character.  When
              the history file is read, lines beginning with the history comment character followed immedi‐
              ately  by  a digit are interpreted as timestamps for the following history entry.  The return
              value is 0 unless an invalid option is encountered, an error occurs while reading or  writing
              the history file, an invalid offset or range is supplied as an argument to -d, or the history
              expansion supplied as an argument to -p fails.

       jobs [-lnprs] [ jobspec ... ]
       jobs -x command [ args ... ]
              The first form lists the active jobs.  The options have the following meanings:
              -l     List process IDs in addition to the normal information.
              -n     Display information only about jobs that have changed status since the user  was  last
                     notified of their status.
              -p     List only the process ID of the job's process group leader.
              -r     Display only running jobs.
              -s     Display only stopped jobs.

              If  jobspec  is given, output is restricted to information about that job.  The return status
              is 0 unless an invalid option is encountered or an invalid jobspec is supplied.

              If the -x option is supplied, jobs replaces any jobspec found in command  or  args  with  the
              corresponding process group ID, and executes command passing it args, returning its exit sta‐
              tus.

       kill [-s sigspec | -n signum | -sigspec] [pid | jobspec] ...
       kill -l|-L [sigspec | exit_status]
              Send the signal named by sigspec or signum to the processes named by pid or jobspec.  sigspec
              is  either a case-insensitive signal name such as SIGKILL (with or without the SIG prefix) or
              a signal number; signum is a signal number.  If sigspec is not present, then SIGTERM  is  as‐
              sumed.   An  argument of -l lists the signal names.  If any arguments are supplied when -l is
              given, the names of the signals corresponding to the arguments are  listed,  and  the  return
              status is 0.  The exit_status argument to -l is a number specifying either a signal number or
              the exit status of a process terminated by a signal.  The -L  option  is  equivalent  to  -l.
              kill  returns  true if at least one signal was successfully sent, or false if an error occurs
              or an invalid option is encountered.

       let arg [arg ...]
              Each arg is an arithmetic expression to be evaluated (see ARITHMETIC EVALUATION  above).   If
              the last arg evaluates to 0, let returns 1; 0 is returned otherwise.

       local [option] [name[=value] ... | - ]
              For  each  argument,  a local variable named name is created, and assigned value.  The option
              can be any of the options accepted by declare.  When local is  used  within  a  function,  it
              causes  the  variable  name to have a visible scope restricted to that function and its chil‐
              dren.  If name is -, the set of shell options is made local to the function in which local is
              invoked:  shell  options  changed  using  the set builtin inside the function are restored to
              their original values when the function returns.  The restore is effected as if a  series  of
              set  commands  were  executed  to  restore the values that were in place before the function.
              With no operands, local writes a list of local variables to the standard output.   It  is  an
              error  to  use local when not within a function.  The return status is 0 unless local is used
              outside a function, an invalid name is supplied, or name is a readonly variable.

       logout Exit a login shell.

       mapfile [-d delim] [-n count] [-O origin] [-s count] [-t] [-u fd] [-C callback] [-c quantum] [array]
       readarray [-d delim] [-n count] [-O origin] [-s count] [-t] [-u fd] [-C callback] [-c quantum]  [ar‐
       ray]
              Read  lines  from  the standard input into the indexed array variable array, or from file de‐
              scriptor fd if the -u option is supplied.  The variable MAPFILE is the  default  array.   Op‐
              tions, if supplied, have the following meanings:
              -d     The  first  character  of delim is used to terminate each input line, rather than new‐
                     line.  If delim is the empty string, mapfile will terminate a line when it reads a NUL
                     character.
              -n     Copy at most count lines.  If count is 0, all lines are copied.
              -O     Begin assigning to array at index origin.  The default index is 0.
              -s     Discard the first count lines read.
              -t     Remove a trailing delim (default newline) from each line read.
              -u     Read lines from file descriptor fd instead of the standard input.
              -C     Evaluate callback each time quantum lines are read.  The -c option specifies quantum.
              -c     Specify the number of lines read between each call to callback.

              If  -C  is specified without -c, the default quantum is 5000.  When callback is evaluated, it
              is supplied the index of the next array element to be assigned and the line to be assigned to
              that  element  as additional arguments.  callback is evaluated after the line is read but be‐
              fore the array element is assigned.

              If not supplied with an explicit origin, mapfile will clear array before assigning to it.

              mapfile returns successfully unless an invalid option or option argument is  supplied,  array
              is invalid or unassignable, or if array is not an indexed array.

       popd [-n] [+n] [-n]
              Removes  entries  from the directory stack.  The elements are numbered from 0 starting at the
              first directory listed by dirs.  With no arguments, popd removes the top directory  from  the
              stack,  and  changes  to  the  new top directory.  Arguments, if supplied, have the following
              meanings:
              -n     Suppresses the normal change of directory when removing directories from the stack, so
                     that only the stack is manipulated.
              +n     Removes  the nth entry counting from the left of the list shown by dirs, starting with
                     zero, from the stack.  For example: ``popd +0'' removes the  first  directory,  ``popd
                     +1'' the second.
              -n     Removes the nth entry counting from the right of the list shown by dirs, starting with
                     zero.  For example: ``popd -0'' removes the last directory, ``popd -1''  the  next  to
                     last.

              If  the  top  element of the directory stack is modified, and the -n option was not supplied,
              popd uses the cd builtin to change to the directory at the top  of  the  stack.   If  the  cd
              fails, popd returns a non-zero value.

              Otherwise,  popd  returns  false  if an invalid option is encountered, the directory stack is
              empty, or a non-existent directory stack entry is specified.

              If the popd command is successful, bash runs dirs to show the final contents of the directory
              stack, and the return status is 0.

       printf [-v var] format [arguments]
              Write the formatted arguments to the standard output under the control of the format.  The -v
              option causes the output to be assigned to the variable var rather than being printed to  the
              standard output.

              The  format  is  a  character string which contains three types of objects: plain characters,
              which are simply copied to standard output, character escape sequences, which  are  converted
              and  copied  to the standard output, and format specifications, each of which causes printing
              of the next successive argument.  In addition to the  standard  printf(1)  format  specifica‐
              tions, printf interprets the following extensions:
              %b     causes  printf  to  expand backslash escape sequences in the corresponding argument in
                     the same way as echo -e.
              %q     causes printf to output the corresponding argument in a format that can be  reused  as
                     shell input.
              %Q     like %q, but applies any supplied precision to the argument before quoting it.
              %(datefmt)T
                     causes  printf to output the date-time string resulting from using datefmt as a format
                     string for strftime(3).  The corresponding argument is  an  integer  representing  the
                     number of seconds since the epoch.  Two special argument values may be used: -1 repre‐
                     sents the current time, and -2 represents the time the shell was invoked.  If no argu‐
                     ment  is  specified, conversion behaves as if -1 had been given.  This is an exception
                     to the usual printf behavior.

              The %b, %q, and %T directives all use the field width and precision arguments from the format
              specification  and write that many bytes from (or use that wide a field for) the expanded ar‐
              gument, which usually contains more characters than the original.

              Arguments to non-string format specifiers are treated as C constants, except that  a  leading
              plus  or minus sign is allowed, and if the leading character is a single or double quote, the
              value is the ASCII value of the following character.

              The format is reused as necessary to consume all of the arguments.  If  the  format  requires
              more  arguments  than are supplied, the extra format specifications behave as if a zero value
              or null string, as appropriate, had been supplied.  The return value is zero on success, non-
              zero on failure.

       pushd [-n] [+n] [-n]
       pushd [-n] [dir]
              Adds  a directory to the top of the directory stack, or rotates the stack, making the new top
              of the stack the current working directory.  With no arguments, pushd exchanges the  top  two
              elements of the directory stack.  Arguments, if supplied, have the following meanings:
              -n     Suppresses  the  normal change of directory when rotating or adding directories to the
                     stack, so that only the stack is manipulated.
              +n     Rotates the stack so that the nth directory (counting from the left of the list  shown
                     by dirs, starting with zero) is at the top.
              -n     Rotates the stack so that the nth directory (counting from the right of the list shown
                     by dirs, starting with zero) is at the top.
              dir    Adds dir to the directory stack at the top

              After the stack has been modified, if the -n option was  not  supplied,  pushd  uses  the  cd
              builtin to change to the directory at the top of the stack.  If the cd fails, pushd returns a
              non-zero value.

              Otherwise, if no arguments are supplied, pushd returns 0 unless the directory stack is empty.
              When  rotating  the directory stack, pushd returns 0 unless the directory stack is empty or a
              non-existent directory stack element is specified.

              If the pushd command is successful, bash runs dirs to show the final contents of  the  direc‐
              tory stack.

       pwd [-LP]
              Print  the absolute pathname of the current working directory.  The pathname printed contains
              no symbolic links if the -P option is supplied or the -o physical option to the  set  builtin
              command  is  enabled.   If  the  -L option is used, the pathname printed may contain symbolic
              links.  The return status is 0 unless an error occurs while reading the name of  the  current
              directory or an invalid option is supplied.

       read [-ers] [-a aname] [-d delim] [-i text] [-n nchars] [-N nchars] [-p prompt] [-t timeout] [-u fd]
       [name ...]
              One line is read from the standard input, or from the file descriptor fd supplied as an argu‐
              ment  to  the  -u  option,  split into words as described above under Word Splitting, and the
              first word is assigned to the first name, the second word to the second name, and so on.   If
              there are more words than names, the remaining words and their intervening delimiters are as‐
              signed to the last name.  If there are fewer words read from the input stream than names, the
              remaining  names are assigned empty values.  The characters in IFS are used to split the line
              into words using the same rules the shell uses for  expansion  (described  above  under  Word
              Splitting).   The  backslash  character (\) may be used to remove any special meaning for the
              next character read and for line continuation.  Options,  if  supplied,  have  the  following
              meanings:
              -a aname
                     The  words are assigned to sequential indices of the array variable aname, starting at
                     0.  aname is unset before any new values are assigned.  Other name arguments  are  ig‐
                     nored.
              -d delim
                     The first character of delim is used to terminate the input line, rather than newline.
                     If delim is the empty string, read will terminate a line when it reads a  NUL  charac‐
                     ter.
              -e     If the standard input is coming from a terminal, readline (see READLINE above) is used
                     to obtain the line.  Readline uses the current (or default, if line  editing  was  not
                     previously active) editing settings, but uses readline's default filename completion.
              -i text
                     If readline is being used to read the line, text is placed into the editing buffer be‐
                     fore editing begins.
              -n nchars
                     read returns after reading nchars characters rather than waiting for a  complete  line
                     of  input,  but honors a delimiter if fewer than nchars characters are read before the
                     delimiter.
              -N nchars
                     read returns after reading exactly nchars characters rather than waiting  for  a  com‐
                     plete  line  of input, unless EOF is encountered or read times out.  Delimiter charac‐
                     ters encountered in the input are not treated specially and do not cause read  to  re‐
                     turn  until  nchars characters are read.  The result is not split on the characters in
                     IFS; the intent is that the variable is assigned exactly the characters read (with the
                     exception of backslash; see the -r option below).
              -p prompt
                     Display  prompt  on  standard  error, without a trailing newline, before attempting to
                     read any input.  The prompt is displayed only if input is coming from a terminal.
              -r     Backslash does not act as an escape character.  The backslash is considered to be part
                     of  the  line.  In particular, a backslash-newline pair may not then be used as a line
                     continuation.
              -s     Silent mode.  If input is coming from a terminal, characters are not echoed.
              -t timeout
                     Cause read to time out and return failure if a complete line of input (or a  specified
                     number  of  characters)  is not read within timeout seconds.  timeout may be a decimal
                     number with a fractional portion following the decimal point.  This option is only ef‐
                     fective  if read is reading input from a terminal, pipe, or other special file; it has
                     no effect when reading from regular files.  If read times out, read saves any  partial
                     input  read  into  the specified variable name.  If timeout is 0, read returns immedi‐
                     ately, without trying to read any data.  The exit status is 0 if input is available on
                     the  specified  file descriptor, or the read will return EOF, non-zero otherwise.  The
                     exit status is greater than 128 if the timeout is exceeded.
              -u fd  Read input from file descriptor fd.

              If no names are supplied, the line read, without the ending delimiter but  otherwise  unmodi‐
              fied,  is assigned to the variable REPLY.  The exit status is zero, unless end-of-file is en‐
              countered, read times out (in which case the status is greater than 128), a variable  assign‐
              ment  error  (such as assigning to a readonly variable) occurs, or an invalid file descriptor
              is supplied as the argument to -u.

       readonly [-aAf] [-p] [name[=word] ...]
              The given names are marked readonly; the values of these names may not be changed  by  subse‐
              quent assignment.  If the -f option is supplied, the functions corresponding to the names are
              so marked.  The -a option restricts the variables to indexed arrays; the -A option  restricts
              the  variables to associative arrays.  If both options are supplied, -A takes precedence.  If
              no name arguments are given, or if the -p option is supplied, a list of all readonly names is
              printed.   The  other  options  may  be used to restrict the output to a subset of the set of
              readonly names.  The -p option causes output to be displayed in a format that may  be  reused
              as input.  If a variable name is followed by =word, the value of the variable is set to word.
              The return status is 0 unless an invalid option is encountered, one of the  names  is  not  a
              valid shell variable name, or -f is supplied with a name that is not a function.

       return [n]
              Causes  a function to stop executing and return the value specified by n to its caller.  If n
              is omitted, the return status is that of the last command executed in the function body.   If
              return  is  executed  by a trap handler, the last command used to determine the status is the
              last command executed before the trap handler.  If return is executed during  a  DEBUG  trap,
              the  last  command used to determine the status is the last command executed by the trap han‐
              dler before return was invoked.  If return is used outside a function, but  during  execution
              of a script by the .  (source) command, it causes the shell to stop executing that script and
              return either n or the exit status of the last command executed within the script as the exit
              status  of  the  script.  If n is supplied, the return value is its least significant 8 bits.
              The return status is non-zero if return is supplied a non-numeric argument, or is  used  out‐
              side  a function and not during execution of a script by . or source.  Any command associated
              with the RETURN trap is executed before execution resumes after the function or script.

       set [-abefhkmnptuvxBCEHPT] [-o option-name] [--] [-] [arg ...]
       set [+abefhkmnptuvxBCEHPT] [+o option-name] [--] [-] [arg ...]
              Without options, display the name and value of each shell variable in a format  that  can  be
              reused  as  input  for setting or resetting the currently-set variables.  Read-only variables
              cannot be reset.  In posix mode, only shell variables are listed.  The output is  sorted  ac‐
              cording  to  the  current  locale.   When  options are specified, they set or unset shell at‐
              tributes.  Any arguments remaining after option processing are treated as values for the  po‐
              sitional  parameters  and are assigned, in order, to $1, $2, ...  $n.  Options, if specified,
              have the following meanings:
              -a      Each variable or function that is created or modified is given the  export  attribute
                      and marked for export to the environment of subsequent commands.
              -b      Report  the  status of terminated background jobs immediately, rather than before the
                      next primary prompt.  This is effective only when job control is enabled.
              -e      Exit immediately if a pipeline (which may consist of  a  single  simple  command),  a
                      list,  or a compound command (see SHELL GRAMMAR above), exits with a non-zero status.
                      The shell does not exit if the command that fails is part of the command list immedi‐
                      ately  following  a while or until keyword, part of the test following the if or elif
                      reserved words, part of any command executed in a && or || list  except  the  command
                      following  the final && or ||, any command in a pipeline but the last, or if the com‐
                      mand's return value is being inverted with !.  If a compound  command  other  than  a
                      subshell  returns  a  non-zero status because a command failed while -e was being ig‐
                      nored, the shell does not exit.  A trap on ERR, if set, is executed before the  shell
                      exits.   This  option  applies to the shell environment and each subshell environment
                      separately (see COMMAND EXECUTION ENVIRONMENT above), and may cause subshells to exit
                      before executing all the commands in the subshell.

                      If  a  compound command or shell function executes in a context where -e is being ig‐
                      nored, none of the commands executed within the compound  command  or  function  body
                      will be affected by the -e setting, even if -e is set and a command returns a failure
                      status.  If a compound command or shell function sets -e while executing in a context
                      where -e is ignored, that setting will not have any effect until the compound command
                      or the command containing the function call completes.
              -f      Disable pathname expansion.
              -h      Remember the location of commands as they are looked up for execution.  This  is  en‐
                      abled by default.
              -k      All  arguments in the form of assignment statements are placed in the environment for
                      a command, not just those that precede the command name.
              -m      Monitor mode.  Job control is enabled.  This option is on by default for  interactive
                      shells  on  systems  that support it (see JOB CONTROL above).  All processes run in a
                      separate process group.  When a background job completes, the  shell  prints  a  line
                      containing its exit status.
              -n      Read  commands but do not execute them.  This may be used to check a shell script for
                      syntax errors.  This is ignored by interactive shells.
              -o option-name
                      The option-name can be one of the following:
                      allexport
                              Same as -a.
                      braceexpand
                              Same as -B.
                      emacs   Use an emacs-style command line editing interface.  This is  enabled  by  de‐
                              fault  when  the  shell  is interactive, unless the shell is started with the
                              --noediting option.  This also affects the editing interface  used  for  read
                              -e.
                      errexit Same as -e.
                      errtrace
                              Same as -E.
                      functrace
                              Same as -T.
                      hashall Same as -h.
                      histexpand
                              Same as -H.
                      history Enable  command history, as described above under HISTORY.  This option is on
                              by default in interactive shells.
                      ignoreeof
                              The effect is as if the shell command ``IGNOREEOF=10'' had been executed (see
                              Shell Variables above).
                      keyword Same as -k.
                      monitor Same as -m.
                      noclobber
                              Same as -C.
                      noexec  Same as -n.
                      noglob  Same as -f.
                      nolog   Currently ignored.
                      notify  Same as -b.
                      nounset Same as -u.
                      onecmd  Same as -t.
                      physical
                              Same as -P.
                      pipefail
                              If  set,  the return value of a pipeline is the value of the last (rightmost)
                              command to exit with a non-zero status, or zero if all commands in the  pipe‐
                              line exit successfully.  This option is disabled by default.
                      posix   Change  the  behavior  of  bash  where the default operation differs from the
                              POSIX standard to match the standard (posix mode).  See SEE ALSO below for  a
                              reference to a document that details how posix mode affects bash's behavior.
                      privileged
                              Same as -p.
                      verbose Same as -v.
                      vi      Use a vi-style command line editing interface.  This also affects the editing
                              interface used for read -e.
                      xtrace  Same as -x.
                      If -o is supplied with no option-name, the values of the current options are printed.
                      If  +o is supplied with no option-name, a series of set commands to recreate the cur‐
                      rent option settings is displayed on the standard output.
              -p      Turn on privileged mode.  In this mode, the $ENV and $BASH_ENV  files  are  not  pro‐
                      cessed,  shell  functions  are not inherited from the environment, and the SHELLOPTS,
                      BASHOPTS, CDPATH, and GLOBIGNORE variables, if they appear in  the  environment,  are
                      ignored.  If the shell is started with the effective user (group) id not equal to the
                      real user (group) id, and the -p option is not supplied, these actions are taken  and
                      the  effective  user  id is set to the real user id.  If the -p option is supplied at
                      startup, the effective user id is not reset.  Turning this option off causes the  ef‐
                      fective user and group ids to be set to the real user and group ids.
              -r      Enable restricted shell mode.  This option cannot be unset once it has been set.
              -t      Exit after reading and executing one command.
              -u      Treat  unset  variables and parameters other than the special parameters "@" and "*",
                      or array variables subscripted with "@" or "*", as an error when performing parameter
                      expansion.   If  expansion  is attempted on an unset variable or parameter, the shell
                      prints an error message, and, if not interactive, exits with a non-zero status.
              -v      Print shell input lines as they are read.
              -x      After expanding each simple command, for command, case command,  select  command,  or
                      arithmetic  for  command,  display the expanded value of PS4, followed by the command
                      and its expanded arguments or associated word list.
              -B      The shell performs brace expansion (see Brace Expansion above).  This is  on  by  de‐
                      fault.
              -C      If  set,  bash does not overwrite an existing file with the >, >&, and <> redirection
                      operators.  This may be overridden when creating output files by using the  redirect‐
                      ion operator >| instead of >.
              -E      If  set,  any trap on ERR is inherited by shell functions, command substitutions, and
                      commands executed in a subshell environment.  The ERR trap is normally not  inherited
                      in such cases.
              -H      Enable !  style history substitution.  This option is on by default when the shell is
                      interactive.
              -P      If set, the shell does not resolve symbolic links when executing commands such as  cd
                      that  change the current working directory.  It uses the physical directory structure
                      instead.  By default, bash follows the logical chain of directories  when  performing
                      commands which change the current directory.
              -T      If  set, any traps on DEBUG and RETURN are inherited by shell functions, command sub‐
                      stitutions, and commands executed in a subshell environment.  The  DEBUG  and  RETURN
                      traps are normally not inherited in such cases.
              --      If no arguments follow this option, then the positional parameters are unset.  Other‐
                      wise, the positional parameters are set to the args, even if some of them begin  with
                      a -.
              -       Signal  the end of options, cause all remaining args to be assigned to the positional
                      parameters.  The -x and -v options are turned off.  If there are no args,  the  posi‐
                      tional parameters remain unchanged.

              The  options  are  off by default unless otherwise noted.  Using + rather than - causes these
              options to be turned off.  The options can also be specified as arguments to an invocation of
              the  shell.  The current set of options may be found in $-.  The return status is always true
              unless an invalid option is encountered.

       shift [n]
              The positional parameters from n+1 ... are renamed to $1 ....  Parameters represented by  the
              numbers  $#  down to $#-n+1 are unset.  n must be a non-negative number less than or equal to
              $#.  If n is 0, no parameters are changed.  If n is not given, it is assumed to be 1.   If  n
              is  greater than $#, the positional parameters are not changed.  The return status is greater
              than zero if n is greater than $# or less than zero; otherwise 0.

       shopt [-pqsu] [-o] [optname ...]
              Toggle the values of settings controlling optional shell behavior.  The settings can  be  ei‐
              ther  those listed below, or, if the -o option is used, those available with the -o option to
              the set builtin command.  With no options, or with the -p option, a list of all settable  op‐
              tions  is  displayed,  with an indication of whether or not each is set; if optnames are sup‐
              plied, the output is restricted to those options.  The -p option causes  output  to  be  dis‐
              played in a form that may be reused as input.  Other options have the following meanings:
              -s     Enable (set) each optname.
              -u     Disable (unset) each optname.
              -q     Suppresses normal output (quiet mode); the return status indicates whether the optname
                     is set or unset.  If multiple optname arguments are given with -q, the  return  status
                     is zero if all optnames are enabled; non-zero otherwise.
              -o     Restricts  the  values  of  optname  to  be those defined for the -o option to the set
                     builtin.

              If either -s or -u is used with no optname arguments, shopt shows only  those  options  which
              are  set or unset, respectively.  Unless otherwise noted, the shopt options are disabled (un‐
              set) by default.

              The return status when listing options is zero if all optnames are enabled,  non-zero  other‐
              wise.   When setting or unsetting options, the return status is zero unless an optname is not
              a valid shell option.

              The list of shopt options is:

              assoc_expand_once
                      If set, the shell suppresses multiple evaluation of associative array subscripts dur‐
                      ing arithmetic expression evaluation, while executing builtins that can perform vari‐
                      able assignments, and while executing builtins that perform array dereferencing.
              autocd  If set, a command name that is the name of a directory is executed as if it were  the
                      argument to the cd command.  This option is only used by interactive shells.
              cdable_vars
                      If  set,  an argument to the cd builtin command that is not a directory is assumed to
                      be the name of a variable whose value is the directory to change to.
              cdspell If set, minor errors in the spelling of a directory component in a cd command will be
                      corrected.   The  errors  checked for are transposed characters, a missing character,
                      and one character too many.  If a correction is  found,  the  corrected  filename  is
                      printed, and the command proceeds.  This option is only used by interactive shells.
              checkhash
                      If  set,  bash  checks that a command found in the hash table exists before trying to
                      execute it.  If a hashed command no longer exists, a normal path search is performed.
              checkjobs
                      If set, bash lists the status of any stopped and running jobs before exiting  an  in‐
                      teractive  shell.  If any jobs are running, this causes the exit to be deferred until
                      a second exit is attempted without an intervening command (see  JOB  CONTROL  above).
                      The shell always postpones exiting if any jobs are stopped.
              checkwinsize
                      If set, bash checks the window size after each external (non-builtin) command and, if
                      necessary, updates the values of LINES and COLUMNS.  This option is  enabled  by  de‐
                      fault.
              cmdhist If  set,  bash attempts to save all lines of a multiple-line command in the same his‐
                      tory entry.  This allows easy re-editing of multi-line commands.  This option is  en‐
                      abled  by default, but only has an effect if command history is enabled, as described
                      above under HISTORY.
              compat31
              compat32
              compat40
              compat41
              compat42
              compat43
              compat44
              compat50
                      These control aspects of the shell's compatibility mode (see SHELL COMPATIBILITY MODE
                      below).

              complete_fullquote
                      If  set,  bash  quotes all shell metacharacters in filenames and directory names when
                      performing completion.  If not set, bash removes metacharacters such  as  the  dollar
                      sign from the set of characters that will be quoted in completed filenames when these
                      metacharacters appear in shell variable references in words to  be  completed.   This
                      means  that  dollar  signs  in  variable names that expand to directories will not be
                      quoted; however, any dollar signs appearing in filenames will not be quoted,  either.
                      This  is  active  only  when  bash is using backslashes to quote completed filenames.
                      This variable is set by default, which is  the  default  bash  behavior  in  versions
                      through 4.2.

              direxpand
                      If  set,  bash  replaces directory names with the results of word expansion when per‐
                      forming filename completion.  This changes the contents of the readline editing  buf‐
                      fer.  If not set, bash attempts to preserve what the user typed.

              dirspell
                      If  set,  bash attempts spelling correction on directory names during word completion
                      if the directory name initially supplied does not exist.

              dotglob If set, bash includes filenames beginning with a `.' in the results of  pathname  ex‐
                      pansion.  The filenames ``.''  and ``..''  must always be matched explicitly, even if
                      dotglob is set.

              execfail
                      If set, a non-interactive shell will not exit if it cannot execute the file specified
                      as  an  argument  to the exec builtin command.  An interactive shell does not exit if
                      exec fails.

              expand_aliases
                      If set, aliases are expanded as described above under ALIASES.  This  option  is  en‐
                      abled by default for interactive shells.

              extdebug
                      If set at shell invocation, or in a shell startup file, arrange to execute the debug‐
                      ger profile before the shell starts, identical to the --debugger option.  If set  af‐
                      ter invocation, behavior intended for use by debuggers is enabled:

                      1.     The  -F  option  to the declare builtin displays the source file name and line
                             number corresponding to each function name supplied as an argument.

                      2.     If the command run by the DEBUG trap returns a non-zero value, the  next  com‐
                             mand is skipped and not executed.

                      3.     If  the  command  run by the DEBUG trap returns a value of 2, and the shell is
                             executing in a subroutine (a shell function or a shell script executed by  the
                             . or source builtins), the shell simulates a call to return.

                      4.     BASH_ARGC and BASH_ARGV are updated as described in their descriptions above).

                      5.     Function  tracing  is enabled: command substitution, shell functions, and sub‐
                             shells invoked with ( command ) inherit the DEBUG and RETURN traps.

                      6.     Error tracing is enabled: command substitution, shell functions, and subshells
                             invoked with ( command ) inherit the ERR trap.

              extglob If  set, the extended pattern matching features described above under Pathname Expan‐
                      sion are enabled.

              extquote
                      If set, $'string' and $"string" quoting is performed within  ${parameter}  expansions
                      enclosed in double quotes.  This option is enabled by default.

              failglob
                      If set, patterns which fail to match filenames during pathname expansion result in an
                      expansion error.

              force_fignore
                      If set, the suffixes specified by the FIGNORE shell variable cause words  to  be  ig‐
                      nored when performing word completion even if the ignored words are the only possible
                      completions.  See SHELL VARIABLES above for a description of FIGNORE.  This option is
                      enabled by default.

              globasciiranges
                      If  set,  range expressions used in pattern matching bracket expressions (see Pattern
                      Matching above) behave as if in the traditional C locale when performing comparisons.
                      That is, the current locale's collating sequence is not taken into account, so b will
                      not collate between A and B, and upper-case and lower-case ASCII characters will col‐
                      late together.

              globskipdots
                      If  set, pathname expansion will never match the filenames ``.''  and ``..'', even if
                      the pattern begins with a ``.''.  This option is enabled by default.

              globstar
                      If set, the pattern ** used in a pathname expansion context will match all files  and
                      zero or more directories and subdirectories.  If the pattern is followed by a /, only
                      directories and subdirectories match.

              gnu_errfmt
                      If set, shell error messages are written in the standard GNU error message format.

              histappend
                      If set, the history list is appended to the file named by the value of  the  HISTFILE
                      variable when the shell exits, rather than overwriting the file.

              histreedit
                      If  set,  and  readline  is  being used, a user is given the opportunity to re-edit a
                      failed history substitution.

              histverify
                      If set, and readline is being used, the results of history substitution are not imme‐
                      diately  passed  to the shell parser.  Instead, the resulting line is loaded into the
                      readline editing buffer, allowing further modification.

              hostcomplete
                      If set, and readline is being used, bash will attempt to perform hostname  completion
                      when  a word containing a @ is being completed (see Completing under READLINE above).
                      This is enabled by default.

              huponexit
                      If set, bash will send SIGHUP to all jobs when an interactive login shell exits.

              inherit_errexit
                      If set, command substitution inherits the value of the errexit option, instead of un‐
                      setting  it  in  the subshell environment.  This option is enabled when posix mode is
                      enabled.

              interactive_comments
                      If set, allow a word beginning with # to cause that word and all remaining characters
                      on that line to be ignored in an interactive shell (see COMMENTS above).  This option
                      is enabled by default.

              lastpipe
                      If set, and job control is not active, the shell runs the last command of a  pipeline
                      not executed in the background in the current shell environment.

              lithist If  set, and the cmdhist option is enabled, multi-line commands are saved to the his‐
                      tory with embedded newlines rather than using semicolon separators where possible.

              localvar_inherit
                      If set, local variables inherit the value and attributes of a variable  of  the  same
                      name  that  exists at a previous scope before any new value is assigned.  The nameref
                      attribute is not inherited.

              localvar_unset
                      If set, calling unset on local variables in previous function scopes  marks  them  so
                      subsequent  lookups find them unset until that function returns. This is identical to
                      the behavior of unsetting local variables at the current function scope.

              login_shell
                      The shell sets this option if it is started as a login shell (see INVOCATION  above).
                      The value may not be changed.

              mailwarn
                      If  set,  and  a file that bash is checking for mail has been accessed since the last
                      time it was checked, the message ``The mail in mailfile has been read'' is displayed.

              no_empty_cmd_completion
                      If set, and readline is being used, bash will not attempt to search the PATH for pos‐
                      sible completions when completion is attempted on an empty line.

              nocaseglob
                      If set, bash matches filenames in a case-insensitive fashion when performing pathname
                      expansion (see Pathname Expansion above).

              nocasematch
                      If set, bash matches patterns in a case-insensitive fashion when performing  matching
                      while executing case or [[ conditional commands, when performing pattern substitution
                      word expansions, or when filtering possible completions as part of programmable  com‐
                      pletion.

              noexpand_translation
                      If  set,  bash encloses the translated results of $"..." quoting in single quotes in‐
                      stead of double quotes.  If the string is not translated, this has no effect.

              nullglob
                      If set, bash allows patterns which match no files (see Pathname Expansion  above)  to
                      expand to a null string, rather than themselves.

              patsub_replacement
                      If  set, bash expands occurrences of & in the replacement string of pattern substitu‐
                      tion to the text matched by the  pattern,  as  described  under  Parameter  Expansion
                      above.  This option is enabled by default.

              progcomp
                      If  set,  the  programmable completion facilities (see Programmable Completion above)
                      are enabled.  This option is enabled by default.

              progcomp_alias
                      If set, and programmable completion is enabled,  bash  treats  a  command  name  that
                      doesn't  have any completions as a possible alias and attempts alias expansion. If it
                      has an alias, bash attempts programmable completion using the command word  resulting
                      from the expanded alias.

              promptvars
                      If  set, prompt strings undergo parameter expansion, command substitution, arithmetic
                      expansion, and quote removal after being expanded as described  in  PROMPTING  above.
                      This option is enabled by default.

              restricted_shell
                      The  shell sets this option if it is started in restricted mode (see RESTRICTED SHELL
                      below).  The value may not be changed.  This is not reset when the startup files  are
                      executed,  allowing  the  startup  files  to  discover  whether or not a shell is re‐
                      stricted.

              shift_verbose
                      If set, the shift builtin prints an error message when the shift  count  exceeds  the
                      number of positional parameters.

              sourcepath
                      If  set, the . (source) builtin uses the value of PATH to find the directory contain‐
                      ing the file supplied as an argument.  This option is enabled by default.

              varredir_close
                      If set, the shell automatically closes file descriptors assigned using the  {varname}
                      redirection syntax (see REDIRECTION above) instead of leaving them open when the com‐
                      mand completes.

              xpg_echo
                      If set, the echo builtin expands backslash-escape sequences by default.

       suspend [-f]
              Suspend the execution of this shell until it receives a SIGCONT signal.  A login shell, or  a
              shell without job control enabled, cannot be suspended; the -f option can be used to override
              this and force the suspension.  The return status is 0 unless the shell is a login  shell  or
              job control is not enabled and -f is not supplied.

       test expr
       [ expr ]
              Return  a  status of 0 (true) or 1 (false) depending on the evaluation of the conditional ex‐
              pression expr.  Each operator and operand must be a separate argument.  Expressions are  com‐
              posed  of  the primaries described above under CONDITIONAL EXPRESSIONS.  test does not accept
              any options, nor does it accept and ignore an argument of -- as signifying  the  end  of  op‐
              tions.

              Expressions  may  be  combined  using  the following operators, listed in decreasing order of
              precedence.  The evaluation depends on the number of arguments; see below.   Operator  prece‐
              dence is used when there are five or more arguments.
              ! expr True if expr is false.
              ( expr )
                     Returns  the value of expr.  This may be used to override the normal precedence of op‐
                     erators.
              expr1 -a expr2
                     True if both expr1 and expr2 are true.
              expr1 -o expr2
                     True if either expr1 or expr2 is true.

              test and [ evaluate conditional expressions using a set of rules based on the number of argu‐
              ments.

              0 arguments
                     The expression is false.
              1 argument
                     The expression is true if and only if the argument is not null.
              2 arguments
                     If  the first argument is !, the expression is true if and only if the second argument
                     is null.  If the first argument is one of the unary conditional operators listed above
                     under  CONDITIONAL  EXPRESSIONS, the expression is true if the unary test is true.  If
                     the first argument is not a valid unary conditional operator, the expression is false.
              3 arguments
                     The following conditions are applied in the order listed.  If the second  argument  is
                     one  of  the  binary conditional operators listed above under CONDITIONAL EXPRESSIONS,
                     the result of the expression is the result of the binary  test  using  the  first  and
                     third  arguments as operands.  The -a and -o operators are considered binary operators
                     when there are three arguments.  If the first argument is !, the value is the negation
                     of  the two-argument test using the second and third arguments.  If the first argument
                     is exactly ( and the third argument is exactly ), the result is the one-argument  test
                     of the second argument.  Otherwise, the expression is false.
              4 arguments
                     The following conditions are applied in the order listed.  If the first argument is !,
                     the result is the negation of the three-argument expression composed of the  remaining
                     arguments.   the two-argument test using the second and third arguments.  If the first
                     argument is exactly ( and the fourth argument is exactly ), the result is the  two-ar‐
                     gument  test  of  the second and third arguments.  Otherwise, the expression is parsed
                     and evaluated according to precedence using the rules listed above.
              5 or more arguments
                     The expression is parsed and evaluated according to precedence using the rules  listed
                     above.

              When used with test or [, the < and > operators sort lexicographically using ASCII ordering.

       times  Print  the  accumulated  user  and  system times for the shell and for processes run from the
              shell.  The return status is 0.

       trap [-lp] [[arg] sigspec ...]
              The command arg is to be read and executed when the shell receives signal(s) sigspec.  If arg
              is  absent (and there is a single sigspec) or -, each specified signal is reset to its origi‐
              nal disposition (the value it had upon entrance to the shell).  If arg is the null string the
              signal  specified by each sigspec is ignored by the shell and by the commands it invokes.  If
              arg is not present and -p has been supplied, then the  trap  commands  associated  with  each
              sigspec  are displayed.  If no arguments are supplied or if only -p is given, trap prints the
              list of commands associated with each signal.  The -l option causes the shell to print a list
              of  signal  names  and their corresponding numbers.  Each sigspec is either a signal name de‐
              fined in <signal.h>, or a signal number.  Signal names are case insensitive and the SIG  pre‐
              fix is optional.

              If a sigspec is EXIT (0) the command arg is executed on exit from the shell.  If a sigspec is
              DEBUG, the command arg is executed before every simple command, for  command,  case  command,
              select  command,  every  arithmetic  for  command, and before the first command executes in a
              shell function (see SHELL GRAMMAR above).  Refer to the description of the extdebug option to
              the  shopt  builtin for details of its effect on the DEBUG trap.  If a sigspec is RETURN, the
              command arg is executed each time a shell function or a script executed with the . or  source
              builtins finishes executing.

              If  a sigspec is ERR, the command arg is executed whenever a pipeline (which may consist of a
              single simple command), a list, or a compound command returns a non-zero exit status, subject
              to  the  following conditions.  The ERR trap is not executed if the failed command is part of
              the command list immediately following a while or until keyword, part of the test  in  an  if
              statement, part of a command executed in a && or || list except the command following the fi‐
              nal && or ||, any command in a pipeline but the last, or if the command's return value is be‐
              ing inverted using !.  These are the same conditions obeyed by the errexit (-e) option.

              Signals ignored upon entry to the shell cannot be trapped or reset.  Trapped signals that are
              not being ignored are reset to their original values in a subshell  or  subshell  environment
              when  one  is  created.  The return status is false if any sigspec is invalid; otherwise trap
              returns true.

       type [-aftpP] name [name ...]
              With no options, indicate how each name would be interpreted if used as a command  name.   If
              the  -t  option  is  used,  type  prints  a  string which is one of alias, keyword, function,
              builtin, or file if name is an alias, shell reserved word, function, builtin, or  disk  file,
              respectively.  If the name is not found, then nothing is printed, and an exit status of false
              is returned.  If the -p option is used, type either returns the name of the  disk  file  that
              would  be  executed  if name were specified as a command name, or nothing if ``type -t name''
              would not return file.  The -P option forces a PATH search for each name, even if  ``type  -t
              name''  would  not  return  file.   If a command is hashed, -p and -P print the hashed value,
              which is not necessarily the file that appears first in PATH.  If the -a option is used, type
              prints  all  of  the places that contain an executable named name.  This includes aliases and
              functions, if and only if the -p option is not also used.  The table of  hashed  commands  is
              not  consulted  when  using  -a.  The -f option suppresses shell function lookup, as with the
              command builtin.  type returns true if all of the arguments are found, false if any  are  not
              found.

       ulimit [-HS] -a
       ulimit [-HS] [-bcdefiklmnpqrstuvxPRT [limit]]
              Provides control over the resources available to the shell and to processes started by it, on
              systems that allow such control.  The -H and -S options specify that the hard or  soft  limit
              is  set  for the given resource.  A hard limit cannot be increased by a non-root user once it
              is set; a soft limit may be increased up to the value of the hard limit.  If neither  -H  nor
              -S  is  specified, both the soft and hard limits are set.  The value of limit can be a number
              in the unit specified for the resource or one of the special values hard, soft, or unlimited,
              which  stand  for the current hard limit, the current soft limit, and no limit, respectively.
              If limit is omitted, the current value of the soft limit of the resource is  printed,  unless
              the  -H  option is given.  When more than one resource is specified, the limit name and unit,
              if appropriate, are printed before the value.  Other options are interpreted as follows:
              -a     All current limits are reported; no limits are set
              -b     The maximum socket buffer size
              -c     The maximum size of core files created
              -d     The maximum size of a process's data segment
              -e     The maximum scheduling priority ("nice")
              -f     The maximum size of files written by the shell and its children
              -i     The maximum number of pending signals
              -k     The maximum number of kqueues that may be allocated
              -l     The maximum size that may be locked into memory
              -m     The maximum resident set size (many systems do not honor this limit)
              -n     The maximum number of open file descriptors (most systems do not allow this  value  to
                     be set)
              -p     The pipe size in 512-byte blocks (this may not be set)
              -q     The maximum number of bytes in POSIX message queues
              -r     The maximum real-time scheduling priority
              -s     The maximum stack size
              -t     The maximum amount of cpu time in seconds
              -u     The maximum number of processes available to a single user
              -v     The  maximum  amount of virtual memory available to the shell and, on some systems, to
                     its children
              -x     The maximum number of file locks
              -P     The maximum number of pseudoterminals
              -R     The maximum time a real-time process can run before blocking, in microseconds
              -T     The maximum number of threads

              If limit is given, and the -a option is not used, limit is the new value of the specified re‐
              source.   If no option is given, then -f is assumed.  Values are in 1024-byte increments, ex‐
              cept for -t, which is in seconds; -R, which is in microseconds; -p,  which  is  in  units  of
              512-byte  blocks;  -P,  -T, -b, -k, -n, and -u, which are unscaled values; and, when in posix
              mode, -c and -f, which are in 512-byte increments.  The return status is 0 unless an  invalid
              option or argument is supplied, or an error occurs while setting a new limit.

       umask [-p] [-S] [mode]
              The  user  file-creation mask is set to mode.  If mode begins with a digit, it is interpreted
              as an octal number; otherwise it is interpreted as a symbolic mode mask similar to  that  ac‐
              cepted  by  chmod(1).   If mode is omitted, the current value of the mask is printed.  The -S
              option causes the mask to be printed in symbolic form; the default output is an octal number.
              If the -p option is supplied, and mode is omitted, the output is in a form that may be reused
              as input.  The return status is 0 if the mode was successfully changed or if no mode argument
              was supplied, and false otherwise.

       unalias [-a] [name ...]
              Remove  each name from the list of defined aliases.  If -a is supplied, all alias definitions
              are removed.  The return value is true unless a supplied name is not a defined alias.

       unset [-fv] [-n] [name ...]
              For each name, remove the corresponding variable or function.  If the  -v  option  is  given,
              each  name refers to a shell variable, and that variable is removed.  Read-only variables may
              not be unset.  If -f is specified, each name refers to a shell  function,  and  the  function
              definition is removed.  If the -n option is supplied, and name is a variable with the nameref
              attribute, name will be unset rather than the variable it references.  -n has  no  effect  if
              the  -f  option  is supplied.  If no options are supplied, each name refers to a variable; if
              there is no variable by that name, a function with that name, if any, is unset.   Each  unset
              variable  or  function is removed from the environment passed to subsequent commands.  If any
              of BASH_ALIASES, BASH_ARGV0,  BASH_CMDS,  BASH_COMMAND,  BASH_SUBSHELL,  BASHPID,  COMP_WORD‐
              BREAKS,  DIRSTACK,  EPOCHREALTIME,  EPOCHSECONDS,  FUNCNAME, GROUPS, HISTCMD, LINENO, RANDOM,
              SECONDS, or SRANDOM are unset, they lose their special properties, even if  they  are  subse‐
              quently reset.  The exit status is true unless a name is readonly or may not be unset.

       wait [-fn] [-p varname] [id ...]
              Wait  for  each  specified child process and return its termination status.  Each id may be a
              process ID or a job specification; if a job spec is given, all processes in that job's  pipe‐
              line  are waited for.  If id is not given, wait waits for all running background jobs and the
              last-executed process substitution, if its process id is the same as $!, and the return  sta‐
              tus  is zero.  If the -n option is supplied, wait waits for a single job from the list of ids
              or, if no ids are supplied, any job, to complete and returns its exit status.  If none of the
              supplied arguments is a child of the shell, or if no arguments are supplied and the shell has
              no unwaited-for children, the exit status is 127.  If the -p option is supplied, the  process
              or  job  identifier of the job for which the exit status is returned is assigned to the vari‐
              able varname named by the option argument.  The variable will be unset initially, before  any
              assignment.   This  is  useful only when the -n option is supplied.  Supplying the -f option,
              when job control is enabled, forces wait to wait for id to  terminate  before  returning  its
              status,  instead of returning when it changes status.  If id specifies a non-existent process
              or job, the return status is 127.  If wait is interrupted by a signal, the return status will
              be  greater  than 128, as described under SIGNALS above.  Otherwise, the return status is the
              exit status of the last process or job waited for.

SHELL COMPATIBILITY MODE
       Bash-4.0 introduced the concept of a shell compatibility level, specified as a set of options to the
       shopt  builtin ( compat31, compat32, compat40, compat41, and so on).  There is only one current com‐
       patibility level -- each option is mutually exclusive.  The compatibility level is intended to allow
       users  to select behavior from previous versions that is incompatible with newer versions while they
       migrate scripts to use current features and behavior. It's intended to be a temporary solution.

       This section does not mention behavior that is standard for a particular version (e.g., setting com‐
       pat32 means that quoting the rhs of the regexp matching operator quotes special regexp characters in
       the word, which is default behavior in bash-3.2 and subsequent versions).

       If a user enables, say, compat32, it may affect the behavior of other compatibility levels up to and
       including  the  current compatibility level.  The idea is that each compatibility level controls be‐
       havior that changed in that version of bash, but that behavior may have been present in earlier ver‐
       sions.   For  instance,  the  change  to  use  locale-based  comparisons with the [[ command came in
       bash-4.1, and earlier versions used ASCII-based comparisons, so enabling compat32 will enable ASCII-
       based  comparisons  as  well.   That granularity may not be sufficient for all uses, and as a result
       users should employ compatibility levels carefully.  Read the documentation for a particular feature
       to find out the current behavior.

       Bash-4.3 introduced a new shell variable: BASH_COMPAT.  The value assigned to this variable (a deci‐
       mal version number like 4.2, or an integer corresponding to the compatNN option, like 42) determines
       the compatibility level.

       Starting  with bash-4.4, Bash has begun deprecating older compatibility levels.  Eventually, the op‐
       tions will be removed in favor of BASH_COMPAT.

       Bash-5.0 is the final version for which there will be an individual shopt option  for  the  previous
       version. Users should use BASH_COMPAT on bash-5.0 and later versions.

       The  following  table describes the behavior changes controlled by each compatibility level setting.
       The compatNN tag is used as shorthand for setting the compatibility level to NN  using  one  of  the
       following  mechanisms.  For versions prior to bash-5.0, the compatibility level may be set using the
       corresponding compatNN shopt option.  For bash-4.3 and later versions, the BASH_COMPAT  variable  is
       preferred, and it is required for bash-5.1 and later versions.

       compat31
              •      quoting  the  rhs of the [[ command's regexp matching operator (=~) has no special ef‐
                     fect

       compat32
              •      interrupting a command list such as "a ; b ; c" causes the execution of the next  com‐
                     mand in the list (in bash-4.0 and later versions, the shell acts as if it received the
                     interrupt, so interrupting one command in a list aborts the execution  of  the  entire
                     list)

       compat40
              •      the  <  and > operators to the [[ command do not consider the current locale when com‐
                     paring strings; they use ASCII ordering.  Bash versions prior to  bash-4.1  use  ASCII
                     collation  and  strcmp(3);  bash-4.1  and later use the current locale's collation se‐
                     quence and strcoll(3).

       compat41
              •      in posix mode, time may be followed by options and still be recognized as  a  reserved
                     word (this is POSIX interpretation 267)
              •      in  posix  mode, the parser requires that an even number of single quotes occur in the
                     word portion of a double-quoted parameter expansion and treats them specially, so that
                     characters  within  the single quotes are considered quoted (this is POSIX interpreta‐
                     tion 221)

       compat42
              •      the replacement string in double-quoted pattern substitution does  not  undergo  quote
                     removal, as it does in versions after bash-4.2
              •      in posix mode, single quotes are considered special when expanding the word portion of
                     a double-quoted parameter expansion and can be used to quote a closing brace or  other
                     special  character (this is part of POSIX interpretation 221); in later versions, sin‐
                     gle quotes are not special within double-quoted word expansions

       compat43
              •      the shell does not print a warning message if an attempt is made to use a quoted  com‐
                     pound  assignment as an argument to declare (e.g., declare -a foo='(1 2)'). Later ver‐
                     sions warn that this usage is deprecated
              •      word expansion errors are considered non-fatal errors that cause the  current  command
                     to  fail,  even  in posix mode (the default behavior is to make them fatal errors that
                     cause the shell to exit)
              •      when executing a shell function, the loop state (while/until/etc.)  is not  reset,  so
                     break  or  continue  in that function will break or continue loops in the calling con‐
                     text. Bash-4.4 and later reset the loop state to prevent this

       compat44
              •      the shell sets up the values used by BASH_ARGV and BASH_ARGC so they can expand to the
                     shell's positional parameters even if extended debugging mode is not enabled
              •      a subshell inherits loops from its parent context, so break or continue will cause the
                     subshell to exit.  Bash-5.0 and later reset the loop state to prevent the exit
              •      variable assignments preceding builtins like export and readonly that  set  attributes
                     continue to affect variables with the same name in the calling environment even if the
                     shell is not in posix mode

       compat50
              •      Bash-5.1 changed the way $RANDOM is generated to introduce slightly  more  randomness.
                     If  the shell compatibility level is set to 50 or lower, it reverts to the method from
                     bash-5.0 and previous versions, so seeding the random number generator by assigning  a
                     value to RANDOM will produce the same sequence as in bash-5.0
              •      If  the command hash table is empty, bash versions prior to bash-5.1 printed an infor‐
                     mational message to that effect, even when producing output that can be reused as  in‐
                     put. Bash-5.1 suppresses that message when the -l option is supplied.

       compat51
              •      The  unset  builtin  treats attempts to unset array subscripts @ and * differently de‐
                     pending on whether the array is indexed or associative, and differently than in previ‐
                     ous versions.

RESTRICTED SHELL
       If  bash  is  started with the name rbash, or the -r option is supplied at invocation, the shell be‐
       comes restricted.  A restricted shell is used to set up an  environment  more  controlled  than  the
       standard shell.  It behaves identically to bash with the exception that the following are disallowed
       or not performed:

       •      changing directories with cd

       •      setting or unsetting the values of SHELL, PATH, HISTFILE, ENV, or BASH_ENV

       •      specifying command names containing /

       •      specifying a filename containing a / as an argument to the .  builtin command

       •      specifying a filename containing a slash as an argument to the history builtin command

       •      specifying a filename containing a slash as an argument to the -p option to the hash  builtin
              command

       •      importing function definitions from the shell environment at startup

       •      parsing the value of SHELLOPTS from the shell environment at startup

       •      redirecting output using the >, >|, <>, >&, &>, and >> redirection operators

       •      using the exec builtin command to replace the shell with another command

       •      adding or deleting builtin commands with the -f and -d options to the enable builtin command

       •      using the enable builtin command to enable disabled shell builtins

       •      specifying the -p option to the command builtin command

       •      turning off restricted mode with set +r or shopt -u restricted_shell.

       These restrictions are enforced after any startup files are read.

       When  a  command that is found to be a shell script is executed (see COMMAND EXECUTION above), rbash
       turns off any restrictions in the shell spawned to execute the script.

SEE ALSO
       Bash Reference Manual, Brian Fox and Chet Ramey
       The Gnu Readline Library, Brian Fox and Chet Ramey
       The Gnu History Library, Brian Fox and Chet Ramey
       Portable Operating System Interface (POSIX) Part 2: Shell and Utilities, IEEE --
              http://pubs.opengroup.org/onlinepubs/9699919799/
       http://tiswww.case.edu/~chet/bash/POSIX -- a description of posix mode
       sh(1), ksh(1), csh(1)
       emacs(1), vi(1)
       readline(3)

FILES
       /bin/bash
              The bash executable
       /etc/profile
              The systemwide initialization file, executed for login shells
       /etc/bash.bashrc
              The systemwide per-interactive-shell startup file
       /etc/bash.bash.logout
              The systemwide login shell cleanup file, executed when a login shell exits
       ~/.bash_profile
              The personal initialization file, executed for login shells
       ~/.bashrc
              The individual per-interactive-shell startup file
       ~/.bash_logout
              The individual login shell cleanup file, executed when a login shell exits
       ~/.bash_history
              The default value of HISTFILE, the file in which bash saves the command history
       ~/.inputrc
              Individual readline initialization file

AUTHORS
       Brian Fox, Free Software Foundation
       bfox@gnu.org

       Chet Ramey, Case Western Reserve University
       chet.ramey@case.edu

BUG REPORTS
       If you find a bug in bash, you should report it.  But first, you should make sure that it really  is
       a  bug,  and  that it appears in the latest version of bash.  The latest version is always available
       from  ftp://ftp.gnu.org/pub/gnu/bash/  and  http://git.savannah.gnu.org/cgit/bash.git/snapshot/bash-
       master.tar.gz.

       Once you have determined that a bug actually exists, use the bashbug command to submit a bug report.
       If you have a fix, you are encouraged to mail that as well!  Suggestions and `philosophical' bug re‐
       ports may be mailed to bug-bash@gnu.org or posted to the Usenet newsgroup gnu.bash.bug.

       ALL bug reports should include:

       The version number of bash
       The hardware and operating system
       The compiler used to compile
       A description of the bug behaviour
       A short script or `recipe' which exercises the bug

       bashbug  inserts  the first three items automatically into the template it provides for filing a bug
       report.

       Comments and bug reports concerning this manual page should be directed to chet.ramey@case.edu.

BUGS
       It's too big and too slow.

       There are some subtle differences between bash and traditional versions of sh, mostly because of the
       POSIX specification.

       Aliases are confusing in some uses.

       Shell builtin commands and functions are not stoppable/restartable.

       Compound  commands  and  command  sequences  of the form `a ; b ; c' are not handled gracefully when
       process suspension is attempted.  When a process is stopped, the shell immediately executes the next
       command in the sequence.  It suffices to place the sequence of commands between parentheses to force
       it into a subshell, which may be stopped as a unit.

       Array variables may not (yet) be exported.

       There may be only one active coprocess at a time.

GNU Bash 5.2                                 2022 September 19                                      BASH(1)

## tldr bash
bash

[0m[0mBourne-Again SHell, an sh-compatible command-line interpreter.
See also: zsh, ! (history expansion).
More information: https://www.gnu.org/software/bash/manual/bash.html#Invoking-Bash.

 - [0m[32;23;22;24;25mStart an interactive shell session:
   [33;23;22;24;25mbash[0m
[0m
 - [0m[32;23;22;24;25mStart an interactive shell session without loading startup configs:
   [33;23;22;24;25mbash --norc[0m
[0m
 - [0m[32;23;22;24;25mExecute specific [c]ommands:
   [33;23;22;24;25mbash -c "[0mecho 'bash is executed'[33;23;22;24;25m"[0m
[0m
 - [0m[32;23;22;24;25mExecute a specific script:
   [33;23;22;24;25mbash [0mpath/to/script.sh
[0m
 - [0m[32;23;22;24;25mE[x]ecute a specific script, printing each command before executing it:
   [33;23;22;24;25mbash -x [0mpath/to/script.sh
[0m
 - [0m[32;23;22;24;25mExecute a specific script and stop at the first [e]rror:
   [33;23;22;24;25mbash -e [0mpath/to/script.sh
[0m
 - [0m[32;23;22;24;25mExecute specific commands from stdin:
   echo "echo 'bash is executed'"[33;23;22;24;25m | bash[0m
[0m
 - [0m[32;23;22;24;25mStart a [r]estricted shell session:
   [33;23;22;24;25mbash [0m[-r|--restricted]
[0m[0m

# batcat

## man batcat
NO INFORMATION

## tldr batcat
batcat

[0m[0mThis command is an alias of bat.

 - [0m[32;23;22;24;25mView documentation for the original command:
   [33;23;22;24;25mtldr bat[0m
[0m[0m

# bc

## man bc
bc(1)                                     General Commands Manual                                     bc(1)

NAME
       bc - An arbitrary precision calculator language

SYNTAX
       bc [ -hlwsqv ] [long-options] [  file ... ]

DESCRIPTION
       bc is a language that supports arbitrary precision numbers with interactive execution of statements.
       There are some similarities in the syntax to the C programming language.  A standard math library is
       available  by  command line option.  If requested, the math library is defined before processing any
       files.  bc starts by processing code from all the files listed on the  command  line  in  the  order
       listed.   After  all  files have been processed, bc reads from the standard input.  All code is exe‐
       cuted as it is read.  (If a file contains a command to halt the processor, bc will never  read  from
       the standard input.)

       This  version  of bc contains several extensions beyond traditional bc implementations and the POSIX
       draft standard.  Command line options can cause these extensions to print a warning  or  to  be  re‐
       jected.   This document describes the language accepted by this processor.  Extensions will be iden‐
       tified as such.

   OPTIONS
       -h, --help
              Print the usage and exit.

       -i, --interactive
              Force interactive mode.

       -l, --mathlib
              Define the standard math library.

       -w, --warn
              Give warnings for extensions to POSIX bc.

       -s, --standard
              Process exactly the POSIX bc language.

       -q, --quiet
              Do not print the normal GNU bc welcome.

       -v, --version
              Print the version number and copyright and quit.

   NUMBERS
       The most basic element in bc is the number.  Numbers are arbitrary precision numbers.   This  preci‐
       sion is both in the integer part and the fractional part.  All numbers are represented internally in
       decimal and all computation is done in decimal.  (This version truncates  results  from  divide  and
       multiply operations.)  There are two attributes of numbers, the length and the scale.  The length is
       the total number of decimal digits used by bc to represent a number and the scale is the total  num‐
       ber of decimal digits after the decimal point.  For example:
               .000001 has a length of 6 and scale of 6.
               1935.000 has a length of 7 and a scale of 3.

   VARIABLES
       Numbers  are  stored  in two types of variables, simple variables and arrays.  Both simple variables
       and array variables are named.  Names begin with a letter followed by any number of letters,  digits
       and  underscores.   All letters must be lower case.  (Full alpha-numeric names are an extension.  In
       POSIX bc all names are a single lower case letter.)  The type of variable is clear  by  the  context
       because all array variable names will be followed by brackets ([]).

       There  are four special variables, scale, ibase, obase, and last.  scale defines how some operations
       use digits after the decimal point.  The default value of scale is 0.  ibase and  obase  define  the
       conversion  base  for  input  and output numbers.  The default for both input and output is base 10.
       last (an extension) is a variable that has the value of the last printed number.  These will be dis‐
       cussed in further detail where appropriate.  All of these variables may have values assigned to them
       as well as used in expressions.

   COMMENTS
       Comments in bc start with the characters /* and end with the characters */.  Comments may start any‐
       where  and  appear  as  a  single  space in the input.  (This causes comments to delimit other input
       items.  For example, a comment can not be found in the middle of a variable name.)  Comments include
       any newlines (end of line) between the start and the end of the comment.

       To  support the use of scripts for bc, a single line comment has been added as an extension.  A sin‐
       gle line comment starts at a # character and continues to the next end of the line.  The end of line
       character is not part of the comment and is processed normally.

   EXPRESSIONS
       The  numbers  are  manipulated by expressions and statements.  Since the language was designed to be
       interactive, statements and expressions are executed as soon as possible.  There is no  "main"  pro‐
       gram.   Instead,  code is executed as it is encountered.  (Functions, discussed in detail later, are
       defined when encountered.)

       A simple expression is just a constant. bc converts constants into internal  decimal  numbers  using
       the  current input base, specified by the variable ibase. (There is an exception in functions.)  The
       legal values of ibase are 2 through 36. (Bases greater than 16 are an extension.) Assigning a  value
       outside  this range to ibase will result in a value of 2 or 36.  Input numbers may contain the char‐
       acters 0–9 and A–Z. (Note: They must be capitals.  Lower case letters are variable  names.)   Single
       digit  numbers  always  have the value of the digit regardless of the value of ibase. (i.e. A = 10.)
       For multi-digit numbers, bc changes all input digits greater or equal  to  ibase  to  the  value  of
       ibase-1.  This makes the number ZZZ always be the largest 3 digit number of the input base.

       Full  expressions  are  similar to many other high level languages.  Since there is only one kind of
       number, there are no rules for mixing types.  Instead, there are rules on the scale of  expressions.
       Every  expression  has  a  scale.  This is derived from the scale of original numbers, the operation
       performed and in many cases, the value of the variable scale. Legal values of the variable scale are
       0 to the maximum number representable by a C integer.

       In the following descriptions of legal expressions, "expr" refers to a complete expression and "var"
       refers to a simple or an array variable.  A simple variable is just a
              name
       and an array variable is specified as
              name[expr]
       Unless specifically mentioned the scale of the result is the maximum scale of  the  expressions  in‐
       volved.

       - expr The result is the negation of the expression.

       ++ var The variable is incremented by one and the new value is the result of the expression.

       -- var The variable is decremented by one and the new value is the result of the expression.

       var ++
               The  result  of  the expression is the value of the variable and then the variable is incre‐
              mented by one.

       var -- The result of the expression is the value of the variable and then  the  variable  is  decre‐
              mented by one.

       expr + expr
              The result of the expression is the sum of the two expressions.

       expr - expr
              The result of the expression is the difference of the two expressions.

       expr * expr
              The result of the expression is the product of the two expressions.

       expr / expr
              The result of the expression is the quotient of the two expressions.  The scale of the result
              is the value of the variable scale.

       expr % expr
              The result of the expression is the "remainder" and it is computed in the following way.   To
              compute a%b, first a/b is computed to scale digits.  That result is used to compute a-(a/b)*b
              to the scale of the maximum of scale+scale(b) and scale(a).  If scale is set to zero and both
              expressions are integers this expression is the integer remainder function.

       expr ^ expr
              The  result of the expression is the value of the first raised to the second.  The second ex‐
              pression must be an integer.  (If the second expression is not an integer, a warning is  gen‐
              erated  and the expression is truncated to get an integer value.)  The scale of the result is
              scale if the exponent is negative.  If the exponent is positive the scale of  the  result  is
              the minimum of the scale of the first expression times the value of the exponent and the max‐
              imum of scale and the scale of the first expression.  (e.g. scale(a^b) = min(scale(a)*b, max(
              scale, scale(a))).)  It should be noted that expr^0 will always return the value of 1.

       ( expr )
              This alters the standard precedence to force the evaluation of the expression.

       var = expr
              The variable is assigned the value of the expression.

       var <op>= expr
              This  is equivalent to "var = var <op> expr" with the exception that the "var" part is evalu‐
              ated only once.  This can make a difference if "var" is an array.

       Relational expressions are a special kind of expression that always evaluate to 0 or 1, 0 if the re‐
       lation is false and 1 if the relation is true.  These may appear in any legal expression.  (POSIX bc
       requires that relational expressions are used only in if, while, and for statements  and  that  only
       one relational test may be done in them.)  The relational operators are

       expr1 < expr2
              The result is 1 if expr1 is strictly less than expr2.

       expr1 <= expr2
              The result is 1 if expr1 is less than or equal to expr2.

       expr1 > expr2
              The result is 1 if expr1 is strictly greater than expr2.

       expr1 >= expr2
              The result is 1 if expr1 is greater than or equal to expr2.

       expr1 == expr2
              The result is 1 if expr1 is equal to expr2.

       expr1 != expr2
              The result is 1 if expr1 is not equal to expr2.

       Boolean  operations are also legal.  (POSIX bc does NOT have boolean operations).  The result of all
       boolean operations are 0 and 1 (for false and true) as in relational expressions.  The boolean oper‐
       ators are:

       !expr  The result is 1 if expr is 0.

       expr && expr
              The result is 1 if both expressions are non-zero.

       expr || expr
              The result is 1 if either expression is non-zero.

       The expression precedence is as follows: (lowest to highest)
              || operator, left associative
              && operator, left associative
              ! operator, nonassociative
              Relational operators, left associative
              Assignment operator, right associative
              + and - operators, left associative
              *, / and % operators, left associative
              ^ operator, right associative
              unary - operator, nonassociative
              ++ and -- operators, nonassociative

       This  precedence was chosen so that POSIX compliant bc programs will run correctly.  This will cause
       the use of the relational and logical operators to have some unusual behavior when used with assign‐
       ment expressions.  Consider the expression:
              a = 3 < 5

       Most  C  programmers would assume this would assign the result of "3 < 5" (the value 1) to the vari‐
       able "a".  What this does in bc is assign the value 3 to the variable "a" and then compare 3  to  5.
       It is best to use parenthesis when using relational and logical operators with the assignment opera‐
       tors.

       There are a few more special expressions that are provided in bc.  These have to do  with  user  de‐
       fined  functions and standard functions.  They all appear as "name(parameters)".  See the section on
       functions for user defined functions.  The standard functions are:

       length ( expression )
              The value of the length function is the number of significant digits in the expression.

       read ( )
              The read function (an extension) will read a number from the standard  input,  regardless  of
              where the function occurs.   Beware, this can cause problems with the mixing of data and pro‐
              gram in the standard input.  The best use for this function is in a previously  written  pro‐
              gram that needs input from the user, but never allows program code to be input from the user.
              The value of the read function is the number read from the standard input using  the  current
              value of the variable ibase for the conversion base.

       scale ( expression )
              The  value  of  the scale function is the number of digits after the decimal point in the ex‐
              pression.

       sqrt ( expression )
              The value of the sqrt function is the square root of the expression.  If  the  expression  is
              negative, a run time error is generated.

   STATEMENTS
       Statements  (as in most algebraic languages) provide the sequencing of expression evaluation.  In bc
       statements are executed "as soon as possible."  Execution happens when a newline in encountered  and
       there is one or more complete statements.  Due to this immediate execution, newlines are very impor‐
       tant in bc.  In fact, both a semicolon and a newline are used as statement separators.   An  improp‐
       erly  placed  newline  will  cause a syntax error.  Because newlines are statement separators, it is
       possible to hide a newline by using the backslash character.  The sequence "\<nl>",  where  <nl>  is
       the  newline  appears  to  bc  as  whitespace instead of a newline.  A statement list is a series of
       statements separated by semicolons and newlines.  The following is a list of bc statements and  what
       they do: (Things enclosed in brackets ([]) are optional parts of the statement.)

       expression
              This  statement  does  one of two things.  If the expression starts with "<variable> <assign‐
              ment> ...", it is considered to be an assignment statement.  If the expression is not an  as‐
              signment  statement, the expression is evaluated and printed to the output.  After the number
              is printed, a newline is printed.  For example, "a=1" is an assignment statement and  "(a=1)"
              is  an  expression that has an embedded assignment.  All numbers that are printed are printed
              in the base specified by the variable obase.  The  legal  values  for  obase  are  2  through
              BC_BASE_MAX.   (See the section LIMITS.)  For bases 2 through 16, the usual method of writing
              numbers is used.  For bases greater than 16, bc uses a multi-character digit method of print‐
              ing the numbers where each higher base digit is printed as a base 10 number.  The multi-char‐
              acter digits are separated by spaces.  Each digit contains the number of characters  required
              to represent the base ten value of "obase-1".  Since numbers are of arbitrary precision, some
              numbers may not be printable on a single output line.   These  long  numbers  will  be  split
              across lines using the "\" as the last character on a line.  The maximum number of characters
              printed per line is 70.  Due to the interactive nature of bc, printing a  number  causes  the
              side  effect  of  assigning  the printed value to the special variable last.  This allows the
              user to recover the last value printed without having to retype the expression  that  printed
              the  number.   Assigning  to last is legal and will overwrite the last printed value with the
              assigned value.  The newly assigned value will remain until the next number is printed or an‐
              other  value  is  assigned to last.  (Some installations may allow the use of a single period
              (.) which is not part of a number as a short hand notation for for last.)

       string The string is printed to the output.  Strings start with a double quote character and contain
              all characters until the next double quote character.  All characters are take literally, in‐
              cluding any newline.  No newline character is printed after the string.

       print list
              The print statement (an extension) provides another method of output.  The "list" is  a  list
              of  strings and expressions separated by commas.  Each string or expression is printed in the
              order of the list.  No terminating newline is printed.  Expressions are evaluated  and  their
              value  is  printed  and  assigned  to  the variable last.  Strings in the print statement are
              printed to the output and may contain special characters.  Special characters start with  the
              backslash  character  (\).   The special characters recognized by bc are "a" (alert or bell),
              "b" (backspace), "f" (form feed), "n" (newline), "r" (carriage return), "q"  (double  quote),
              "t" (tab), and "\" (backslash).  Any other character following the backslash will be ignored.

       { statement_list }
              This is the compound statement.  It allows multiple statements to be grouped together for ex‐
              ecution.

       if ( expression ) statement1 [else statement2]
              The if statement evaluates the expression and executes statement1 or statement2 depending  on
              the  value  of  the  expression.   If the expression is non-zero, statement1 is executed.  If
              statement2 is present and the value of the expression is  0,  then  statement2  is  executed.
              (The else clause is an extension.)

       while ( expression ) statement
              The  while  statement will execute the statement while the expression is non-zero.  It evalu‐
              ates the expression before each execution of the statement.    Termination  of  the  loop  is
              caused by a zero expression value or the execution of a break statement.

       for ( [expression1] ; [expression2] ; [expression3] ) statement
              The for statement controls repeated execution of the statement.  Expression1 is evaluated be‐
              fore the loop.  Expression2 is evaluated before each execution of the statement.   If  it  is
              non-zero, the statement is evaluated.  If it is zero, the loop is terminated.  After each ex‐
              ecution of the statement, expression3 is evaluated before the  reevaluation  of  expression2.
              If  expression1  or  expression3 are missing, nothing is evaluated at the point they would be
              evaluated.  If expression2 is missing, it is the same as substituting the value 1 for expres‐
              sion2.   (The  optional  expressions  are  an extension.  POSIX bc requires all three expres‐
              sions.)  The following is equivalent code for the for statement:
              expression1;
              while (expression2) {
                 statement;
                 expression3;
              }

       break  This statement causes a forced exit of the most  recent  enclosing  while  statement  or  for
              statement.

       continue
              The continue statement (an extension) causes the most recent enclosing for statement to start
              the next iteration.

       halt   The halt statement (an extension) is an executed statement that causes the  bc  processor  to
              quit  only  when it is executed.  For example, "if (0 == 1) halt" will not cause bc to termi‐
              nate because the halt is not executed.

       return Return the value 0 from a function.  (See the section on functions.)

       return ( expression )
              Return the value of the expression from a function.  (See the section on functions.)   As  an
              extension, the parenthesis are not required.

   PSEUDO STATEMENTS
       These  statements  are  not  statements in the traditional sense.  They are not executed statements.
       Their function is performed at "compile" time.

       limits Print the local limits enforced by the local version of bc.  This is an extension.

       quit   When the quit statement is read, the bc processor is terminated, regardless of where the quit
              statement is found.  For example, "if (0 == 1) quit" will cause bc to terminate.

       warranty
              Print a longer warranty notice.  This is an extension.

   FUNCTIONS
       Functions  provide  a  method of defining a computation that can be executed later.  Functions in bc
       always compute a value and return it to the caller.  Function definitions are "dynamic" in the sense
       that  a  function  is  undefined until a definition is encountered in the input.  That definition is
       then used until another definition function for the same name is encountered.   The  new  definition
       then replaces the older definition.  A function is defined as follows:
              define name ( parameters ) { newline
                  auto_list   statement_list }
       A function call is just an expression of the form "name(parameters)".

       Parameters  are  numbers or arrays (an extension).  In the function definition, zero or more parame‐
       ters are defined by listing their names separated by commas.  All parameters are call by  value  pa‐
       rameters.  Arrays are specified in the parameter definition by the notation "name[]".   In the func‐
       tion call, actual parameters are full expressions for number parameters.  The same notation is  used
       for  passing  arrays  as  for  defining array parameters.  The named array is passed by value to the
       function.  Since function definitions are dynamic, parameter numbers and types are  checked  when  a
       function  is  called.   Any mismatch in number or types of parameters will cause a runtime error.  A
       runtime error will also occur for the call to an undefined function.

       The auto_list is an optional list of variables that are for "local" use.  The  syntax  of  the  auto
       list  (if present) is "auto name, ... ;".  (The semicolon is optional.)  Each name is the name of an
       auto variable.  Arrays may be specified by using the same notation as  used  in  parameters.   These
       variables  have  their  values  pushed onto a stack at the start of the function.  The variables are
       then initialized to zero and used throughout the execution of the function.  At function exit, these
       variables  are  popped  so that the original value (at the time of the function call) of these vari‐
       ables are restored.  The parameters are really auto variables that are initialized to a  value  pro‐
       vided  in  the function call.  Auto variables are different than traditional local variables because
       if function A calls function B, B may access function A's auto variables  by  just  using  the  same
       name, unless function B has called them auto variables.  Due to the fact that auto variables and pa‐
       rameters are pushed onto a stack, bc supports recursive functions.

       The function body is a list of bc statements.  Again, statements are separated by semicolons or new‐
       lines.   Return statements cause the termination of a function and the return of a value.  There are
       two versions of the return statement.  The first form, "return", returns the value 0 to the  calling
       expression.   The second form, "return ( expression )", computes the value of the expression and re‐
       turns that value to the calling expression.  There is an implied "return (0)" at the  end  of  every
       function.  This allows a function to terminate and return 0 without an explicit return statement.

       Functions  also  change the usage of the variable ibase.  All constants in the function body will be
       converted using the value of ibase at the time of the function call.  Changes of ibase will  be  ig‐
       nored  during the execution of the function except for the standard function read, which will always
       use the current value of ibase for conversion of numbers.

       Several extensions have been added to functions.  First, the  format  of  the  definition  has  been
       slightly relaxed.  The standard requires the opening brace be on the same line as the define keyword
       and all other parts must be on following lines.  This version of bc will allow any  number  of  new‐
       lines  before  and  after the opening brace of the function.  For example, the following definitions
       are legal.
              define d (n) { return (2*n); }
              define d (n)
                { return (2*n); }

       Functions may be defined as void.  A void function returns no value and thus may not be used in  any
       place  that  needs a value.  A void function does not produce any output when called by itself on an
       input line.  The key word void is placed between the key word define and the function name.  For ex‐
       ample, consider the following session.
              define py (y) { print "--->", y, "<---", "\n"; }
              define void px (x) { print "--->", x, "<---", "\n"; }
              py(1)
              --->1<---
              0
              px(1)
              --->1<---
       Since  py is not a void function, the call of py(1) prints the desired output and then prints a sec‐
       ond line that is the value of the function.  Since the value of a function that is not given an  ex‐
       plicit  return  statement  is  zero, the zero is printed.  For px(1), no zero is printed because the
       function is a void function.

       Also, call by variable for arrays was added.  To declare a call by variable array,  the  declaration
       of  the  array  parameter in the function definition looks like "*name[]".  The call to the function
       remains the same as call by value arrays.

   MATH LIBRARY
       If bc is invoked with the -l option, a math library is preloaded and the default scale is set to 20.
       The  math  functions  will  calculate their results to the scale set at the time of their call.  The
       math library defines the following functions:

       s (x)  The sine of x, x is in radians.

       c (x)  The cosine of x, x is in radians.

       a (x)  The arctangent of x, arctangent returns radians.

       l (x)  The natural logarithm of x.

       e (x)  The exponential function of raising e to the value x.

       j (n,x)
              The Bessel function of integer order n of x.

   EXAMPLES
       In /bin/sh, the following will assign the value of "pi" to the shell variable pi.
               pi=$(echo "scale=10; 4*a(1)" | bc -l)

       The following is the definition of the exponential function used in the math library.  This function
       is written in POSIX bc.
              scale = 20

              /* Uses the fact that e^x = (e^(x/2))^2
                 When x is small enough, we use the series:
                   e^x = 1 + x + x^2/2! + x^3/3! + ...
              */

              define e(x) {
                auto  a, d, e, f, i, m, v, z

                /* Check the sign of x. */
                if (x<0) {
                  m = 1
                  x = -x
                }

                /* Precondition x. */
                z = scale;
                scale = 4 + z + .44*x;
                while (x > 1) {
                  f += 1;
                  x /= 2;
                }

                /* Initialize the variables. */
                v = 1+x
                a = x
                d = 1

                for (i=2; 1; i++) {
                  e = (a *= x) / (d *= i)
                  if (e == 0) {
                    if (f>0) while (f--)  v = v*v;
                    scale = z
                    if (m) return (1/v);
                    return (v/1);
                  }
                  v += e
                }
              }

       The following is code that uses the extended features of bc to implement a simple program for calcu‐
       lating checkbook balances.  This program is best kept in a file so that it can be  used  many  times
       without having to retype it at every use.
              scale=2
              print "\nCheck book program!\n"
              print "  Remember, deposits are negative transactions.\n"
              print "  Exit by a 0 transaction.\n\n"

              print "Initial balance? "; bal = read()
              bal /= 1
              print "\n"
              while (1) {
                "current balance = "; bal
                "transaction? "; trans = read()
                if (trans == 0) break;
                bal -= trans
                bal /= 1
              }
              quit

       The following is the definition of the recursive factorial function.
              define f (x) {
                if (x <= 1) return (1);
                return (f(x-1) * x);
              }

   READLINE AND LIBEDIT OPTIONS
       GNU  bc can be compiled (via a configure option) to use the GNU readline input editor library or the
       BSD libedit library.  This allows the user to do editing of lines before sending  them  to  bc.   It
       also  allows  for  a history of previous lines typed.  When this option is selected, bc has one more
       special variable.  This special variable, history is the number of lines of history  retained.   For
       readline,  a  value of -1 means that an unlimited number of history lines are retained.  Setting the
       value of history to a positive number restricts the number of history lines  to  the  number  given.
       The  value of 0 disables the history feature.  The default value is 100.  For more information, read
       the user manuals for the GNU readline, history and BSD libedit libraries.  One can not  enable  both
       readline and libedit at the same time.

   DIFFERENCES
       This version of bc was implemented from the POSIX P1003.2/D11 draft and contains several differences
       and extensions relative to the draft and traditional implementations.  It is not implemented in  the
       traditional  way  using  dc(1).   This version is a single process which parses and runs a byte code
       translation of the program.  There is an "undocumented" option (-c) that causes the program to  out‐
       put  the  byte  code to the standard output instead of running it.  It was mainly used for debugging
       the parser and preparing the math library.

       A major source of differences is extensions, where a feature is extended to add  more  functionality
       and  additions,  where  new features are added.  The following is the list of differences and exten‐
       sions.

       LANG environment
              This version does not conform to the POSIX standard in the processing of the LANG environment
              variable and all environment variables starting with LC_.

       names  Traditional  and POSIX bc have single letter names for functions, variables and arrays.  They
              have been extended to be multi-character names that start with a letter and may contain  let‐
              ters, numbers and the underscore character.

       Strings
              Strings  are  not  allowed  to contain NUL characters.  POSIX says all characters must be in‐
              cluded in strings.

       last   POSIX bc does not have a last variable.  Some implementations of bc use the period (.)  in  a
              similar way.

       comparisons
              POSIX bc allows comparisons only in the if statement, the while statement, and the second ex‐
              pression of the for statement.  Also, only one relational operation is  allowed  in  each  of
              those statements.

       if statement, else clause
              POSIX bc does not have an else clause.

       for statement
              POSIX bc requires all expressions to be present in the for statement.

       &&, ||, !
              POSIX bc does not have the logical operators.

       read function
              POSIX bc does not have a read function.

       print statement
              POSIX bc does not have a print statement.

       continue statement
              POSIX bc does not have a continue statement.

       return statement
              POSIX bc requires parentheses around the return expression.

       array parameters
              POSIX bc does not (currently) support array parameters in full.  The POSIX grammar allows for
              arrays in function definitions, but does not provide a method to specify an array as  an  ac‐
              tual  parameter.  (This is most likely an oversight in the grammar.)  Traditional implementa‐
              tions of bc have only call by value array parameters.

       function format
              POSIX bc requires the opening brace on the same line as the define  key  word  and  the  auto
              statement on the next line.

       =+, =-, =*, =/, =%, =^
              POSIX bc does not require these "old style" assignment operators to be defined.  This version
              may allow these "old style" assignments.  Use the limits statement to see  if  the  installed
              version  supports  them.  If it does support the "old style" assignment operators, the state‐
              ment "a =- 1" will decrement a by 1 instead of setting a to the value -1.

       spaces in numbers
              Other implementations of bc allow spaces in numbers.  For example, "x=1 3" would  assign  the
              value 13 to the variable x.  The same statement would cause a syntax error in this version of
              bc.

       errors and execution
              This implementation varies from other implementations in terms of what code will be  executed
              when syntax and other errors are found in the program.  If a syntax error is found in a func‐
              tion definition, error recovery tries to find the beginning of a statement  and  continue  to
              parse  the  function.  Once a syntax error is found in the function, the function will not be
              callable and becomes undefined.  Syntax errors in the interactive execution code will invali‐
              date  the  current execution block.  The execution block is terminated by an end of line that
              appears after a complete sequence of statements.  For example,
              a = 1
              b = 2
       has two execution blocks and
              { a = 1
                b = 2 }
       has one execution block.  Any runtime error will terminate the execution of  the  current  execution
       block.  A runtime warning will not terminate the current execution block.

       Interrupts
              During  an interactive session, the SIGINT signal (usually generated by the control-C charac‐
              ter from the terminal) will cause execution of the current execution block to be interrupted.
              It  will display a "runtime" error indicating which function was interrupted.  After all run‐
              time structures have been cleaned up, a message will be printed to notify the user that bc is
              ready  for  more input.  All previously defined functions remain defined and the value of all
              non-auto variables are the value at the point of interruption.  All auto variables and  func‐
              tion  parameters  are removed during the clean up process.  During a non-interactive session,
              the SIGINT signal will terminate the entire run of bc.

   LIMITS
       The following are the limits currently in place for this bc processor.  Some of them may  have  been
       changed by an installation.  Use the limits statement to see the actual values.

       BC_BASE_MAX
              The maximum output base is currently set at 999.  The maximum input base is 16.

       BC_DIM_MAX
              This  is currently an arbitrary limit of 65535 as distributed.  Your installation may be dif‐
              ferent.

       BC_SCALE_MAX
              The number of digits after the decimal point is limited to INT_MAX digits.  Also, the  number
              of digits before the decimal point is limited to INT_MAX digits.

       BC_STRING_MAX
              The limit on the number of characters in a string is INT_MAX characters.

       exponent
              The value of the exponent in the raise operation (^) is limited to LONG_MAX.

       variable names
              The current limit on the number of unique names is 32767 for each of simple variables, arrays
              and functions.

ENVIRONMENT VARIABLES
       The following environment variables are processed by bc:

       POSIXLY_CORRECT
              This is the same as the -s option.

       BC_ENV_ARGS
              This is another mechanism to get arguments to bc.  The format is the same as the command line
              arguments.  These arguments are processed first, so any files listed in the environment argu‐
              ments are processed before any command line argument files.  This allows the user to  set  up
              "standard" options and files to be processed at every invocation of bc.  The files in the en‐
              vironment variables would typically contain function definitions for functions the user wants
              defined every time bc is run.

       BC_LINE_LENGTH
              This  should be an integer specifying the number of characters in an output line for numbers.
              This includes the backslash and newline characters for long numbers.  As  an  extension,  the
              value of zero disables the multi-line feature.  Any other value of this variable that is less
              than 3 sets the line length to 70.

DIAGNOSTICS
       If any file on the command line can not be opened, bc will report that the file is  unavailable  and
       terminate.  Also, there are compile and run time diagnostics that should be self-explanatory.

BUGS
       Error recovery is not very good yet.

       Email  bug  reports  to  bug-bc@gnu.org.  Be sure to include the word ``bc'' somewhere in the ``Sub‐
       ject:'' field.

AUTHOR
       Philip A. Nelson
       philnelson@acm.org

ACKNOWLEDGEMENTS
       The author would like to thank Steve Sommars (Steve.Sommars@att.com) for his extensive help in test‐
       ing  the  implementation.   Many great suggestions were given.  This is a much better product due to
       his involvement.

GNU Project                                      2006-06-11                                           bc(1)

## tldr bc
bc

[0m[0mAn arbitrary precision calculator language.
See also: dc, qalc.
More information: https://manned.org/bc.

 - [0m[32;23;22;24;25mStart an interactive session:
   [33;23;22;24;25mbc[0m
[0m
 - [0m[32;23;22;24;25mStart an interactive session with the standard math library enabled:
   [33;23;22;24;25mbc [0m[-i|--interactive][33;23;22;24;25m [0m[-l|--mathlib]
[0m
 - [0m[32;23;22;24;25mCalculate an expression:
   [33;23;22;24;25mecho '[0m5 / 3[33;23;22;24;25m' | bc[0m
[0m
 - [0m[32;23;22;24;25mExecute a script:
   [33;23;22;24;25mbc [0mpath/to/script.bc
[0m
 - [0m[32;23;22;24;25mCalculate an expression with the specified scale:
   [33;23;22;24;25mecho 'scale = [0m10[33;23;22;24;25m; [0m5 / 3[33;23;22;24;25m' | bc[0m
[0m
 - [0m[32;23;22;24;25mCalculate a sine/cosine/arctangent/natural logarithm/exponential function using mathlib:
   [33;23;22;24;25mecho '[0ms|c|a|l|e[33;23;22;24;25m([0m1[33;23;22;24;25m)' | bc [0m[-l|--mathlib]
[0m
 - [0m[32;23;22;24;25mExecute an inline factorial script:
   [33;23;22;24;25mecho "define factorial(n) { if (n <= 1) return 1; return n*factorial(n-1); }; factorial([0m10[33;23;22;24;25m)" | bc[0m
[0m[0m

# bg

## man bg
NO INFORMATION

## tldr bg
bg

[0m[0mResume suspended jobs (e.g. using <Ctrl z>), and keep them running in the background.
See also: jobs, fg, disown.
More information: https://www.gnu.org/software/bash/manual/bash.html#index-bg.

 - [0m[32;23;22;24;25mResume the most recently suspended job and run it in the background:
   [33;23;22;24;25mbg[0m
[0m
 - [0m[32;23;22;24;25mResume a specific job and run it in the background (run jobs to find the job number):
   [33;23;22;24;25mbg %[0mjob_number
[0m[0m

# cat

## man cat
CAT(1)                                         User Commands                                         CAT(1)

NAME
       cat - concatenate files and print on the standard output

SYNOPSIS
       cat [OPTION]... [FILE]...

DESCRIPTION
       Concatenate FILE(s) to standard output.

       With no FILE, or when FILE is -, read standard input.

       -A, --show-all
              equivalent to -vET

       -b, --number-nonblank
              number nonempty output lines, overrides -n

       -e     equivalent to -vE

       -E, --show-ends
              display $ at end of each line

       -n, --number
              number all output lines

       -s, --squeeze-blank
              suppress repeated empty output lines

       -t     equivalent to -vT

       -T, --show-tabs
              display TAB characters as ^I

       -u     (ignored)

       -v, --show-nonprinting
              use ^ and M- notation, except for LFD and TAB

       --help display this help and exit

       --version
              output version information and exit

EXAMPLES
       cat f - g
              Output f's contents, then standard input, then g's contents.

       cat    Copy standard input to standard output.

AUTHOR
       Written by Torbjorn Granlund and Richard M. Stallman.

REPORTING BUGS
       GNU coreutils online help: <https://www.gnu.org/software/coreutils/>
       Report any translation bugs to <https://translationproject.org/team/>

COPYRIGHT
       Copyright  ©  2022  Free  Software  Foundation,  Inc.   License  GPLv3+:  GNU GPL version 3 or later
       <https://gnu.org/licenses/gpl.html>.
       This is free software: you are free to change and redistribute it.  There is NO WARRANTY, to the ex‐
       tent permitted by law.

SEE ALSO
       tac(1)

       Full documentation <https://www.gnu.org/software/coreutils/cat>
       or available locally via: info '(coreutils) cat invocation'

GNU coreutils 9.1                              September 2022                                        CAT(1)

## tldr cat
cat

[0m[0mPrint and concatenate files.
More information: https://manned.org/cat.1posix.

 - [0m[32;23;22;24;25mPrint the contents of a file to stdout:
   [33;23;22;24;25mcat [0mpath/to/file
[0m
 - [0m[32;23;22;24;25mConcatenate several files into an output file:
   [33;23;22;24;25mcat [0mpath/to/file1 path/to/file2 ...[33;23;22;24;25m > [0mpath/to/output_file
[0m
 - [0m[32;23;22;24;25mAppend several files to an output file:
   [33;23;22;24;25mcat [0mpath/to/file1 path/to/file2 ...[33;23;22;24;25m >> [0mpath/to/output_file
[0m
 - [0m[32;23;22;24;25mCopy the contents of a file into an output file without buffering:
   [33;23;22;24;25mcat -u [0m/dev/tty12[33;23;22;24;25m > [0m/dev/tty13
[0m
 - [0m[32;23;22;24;25mWrite stdin to a file:
   [33;23;22;24;25mcat - > [0mpath/to/file
[0m[0m

# cd

## man cd
NO INFORMATION

## tldr cd
cd

[0m[0mChange the current working directory.
More information: https://www.gnu.org/software/bash/manual/bash.html#index-cd.

 - [0m[32;23;22;24;25mGo to the specified directory:
   [33;23;22;24;25mcd [0mpath/to/directory
[0m
 - [0m[32;23;22;24;25mGo up to the parent of the current directory:
   [33;23;22;24;25mcd ..[0m
[0m
 - [0m[32;23;22;24;25mGo to the home directory of the current user:
   [33;23;22;24;25mcd[0m
[0m
 - [0m[32;23;22;24;25mGo to the home directory of the specified user:
   [33;23;22;24;25mcd ~[0musername
[0m
 - [0m[32;23;22;24;25mGo to the previously chosen directory:
   [33;23;22;24;25mcd -[0m
[0m
 - [0m[32;23;22;24;25mGo to the root directory:
   [33;23;22;24;25mcd /[0m
[0m[0m

