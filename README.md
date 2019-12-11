# UGR-SO

Memoria de las prácticas de Sistemas Operativos.

## Índice
+ [Módulo I](#modulo1)
  + [Sesión 1](#sesion11)
    + [Ejercicio 1](#ejer11)
    + [Ejercicio 2](#ejer12)
    + [Ejercicio 3](#ejer13)
    + [Ejercicio 4](#ejer14)
    + [Ejercicio 5](#ejer15)
    + [Ejercicio 6](#ejer16)
    + [Ejercicio 7](#ejer17)
    + [Ejercicio 8](#ejer18)
    + [Ejercicio 9](#ejer19)
    + [Ejercicio 10](#ejer110)
    + [Ejercicio 11](#ejer111)
  + [Sesión 2](#sesion12)
+ [Módulo II](#modulo2)
  + [Sesión 1](#sesion1)
    + [Ejercicio 1](#ejer1)
    + [Ejercicio 2](#ejer2)
    + [Ejercicio 3](#ejer3)
    + [Ejercicio 4](#ejer4)
  + [Sesión 2](#sesion2)
    + [Ejercicio 1](#ejer21)
    + [Ejercicio 2](#ejer22)
    + [Ejercicio 3](#ejer23)
    + [Ejercicio 4](#ejer24)
  + [Sesión 3](#sesion3)
    + [Ejercicio 1](#ejer31)
    + [Ejercicio 2](#ejer32)
    + [Ejercicio 3](#ejer33)
    + [Ejercicio 4](#ejer34)
    + [Ejercicio 5](#ejer35)
    + [Ejercicio 6](#ejer36)
    + [Ejercicio 7](#ejer37)
  + [Sesión 4](#sesion4)
    + [Ejercicio 1](#ejer41)
    + [Ejercicio 2](#ejer42)
    + [Ejercicio 3](#ejer43)
    + [Ejercicio 4](#ejer44)
    + [Ejercicio 5](#ejer45)
  + [Sesión 5](#sesion5)



---
<a name="modulo1"></a>
## Módulo I

<a name="sesion11"></a>
### Sesión I

<a name="ejer11"></a>
**Ejercicio 1**. Crea un script de bash que automatice todos los pasos vistos en este punto y que guardarás preferiblemente en tu directorio home. Al entrar de nuevo en el sistema sólo tendrás que ejecutar el script para empezar a trabajar en modo root.

```bash
#!/bin/bash
# Actividad 1.1
# decompress files
7z x ~/Documents/UGR/SO/Fedora14-x86-root_fs.gz -o/tmp/
7z x ~/Documents/UGR/SO/kernel32-3.0.4.gz -o/tmp/

# launch os
cd /tmp
chmod 777 kernel32-3.0.4 Fedora14-x86-root_fs
./kernel32-3.0.4 ubda=./Fedora14-x86-root_fs mem=1024m
```
<a name="ejer12"></a>
**Ejercicio 2**.Visualiza el contenido de los dos archivos anteriores y comprueba cuáles son las opciones por defecto que tendría un usuario que se creara en nuestro sistema. A continuación, crea una cuenta de usuario y visualiza el contenido de los archivos `/etc/passwd` y `/etc/group`, y el directorio `/home` para comprobar que los nuevos datos se han rellenado conforme a la especificación tomada de `/etc/default/useradd` y `/etc/login.defs`.

<details>
<summary>
useradd defaults
</summary>
<p>

```console
[root@localhost ~]# useradd -D
GROUP=100
HOME=/home
INACTIVE=-1
EXPIRE=
SHELL=/bin/bash
SKEL=/etc/skel
CREATE_MAIL_SPOOL=yes
[root@localhost ~]# cat /etc/default/useradd
# useradd defaults file
GROUP=100
HOME=/home
INACTIVE=-1
EXPIRE=
SHELL=/bin/bash
SKEL=/etc/skel
CREATE_MAIL_SPOOL=yes
```

</p>
</details>


<details>
<summary>
/etc/login.defs:
</summary>
<p>

```console
[root@localhost ~]# cat /etc/login.defs
# *REQUIRED*
#   Directory where mailboxes reside, _or_ name of file, relative to the
#   home directory.  If you _do_ define both, MAIL_DIR takes precedence.
#   QMAIL_DIR is for Qmail
#
#QMAIL_DIR	Maildir
MAIL_DIR	/var/spool/mail
#MAIL_FILE	.mail

# Password aging controls:
#
#	PASS_MAX_DAYS	Maximum number of days a password may be used.
#	PASS_MIN_DAYS	Minimum number of days allowed between password changes.
#	PASS_MIN_LEN	Minimum acceptable password length.
#	PASS_WARN_AGE	Number of days warning given before a password expires.
#
PASS_MAX_DAYS	99999
PASS_MIN_DAYS	0
PASS_MIN_LEN	5
PASS_WARN_AGE	7

#
# Min/max values for automatic uid selection in useradd
#
UID_MIN			  500
UID_MAX			60000

#
# Min/max values for automatic gid selection in groupadd
#
GID_MIN			  500
GID_MAX			60000

#
# If defined, this command is run when removing a user.
# It should remove any at/cron/print jobs etc. owned by
# the user to be removed (passed as the first argument).
#
#USERDEL_CMD	/usr/sbin/userdel_local

#
# If useradd should create home directories for users by default
# On RH systems, we do. This option is overridden with the -m flag on
# useradd command line.
#
CREATE_HOME	yes

# The permission mask is initialized to this value. If not specified,
# the permission mask will be initialized to 022.
UMASK           077

# This enables userdel to remove user groups if no members exist.
#
USERGROUPS_ENAB yes

# Use SHA512 to encrypt password.
ENCRYPT_METHOD SHA512
```

</p>
</details>

Ahora procedemos a crear un usuario:

```console
[root@localhost ~]# useradd user
```

y comprobamos que los datos se han rellenado conforme a lo establecido por defecto:

<details>
<summary>
/etc/passwd
</summary>
<p>

```console
[root@localhost ~]# cat /etc/passwd
root::0:0:root:/root:/bin/bash
bin:x:1:1:bin:/bin:/sbin/nologin
daemon:x:2:2:daemon:/sbin:/sbin/nologin
adm:x:3:4:adm:/var/adm:/sbin/nologin
lp:x:4:7:lp:/var/spool/lpd:/sbin/nologin
sync:x:5:0:sync:/sbin:/bin/sync
shutdown:x:6:0:shutdown:/sbin:/sbin/shutdown
halt:x:7:0:halt:/sbin:/sbin/halt
mail:x:8:12:mail:/var/spool/mail:/sbin/nologin
uucp:x:10:14:uucp:/var/spool/uucp:/sbin/nologin
operator:x:11:0:operator:/root:/sbin/nologin
games:x:12:100:games:/usr/games:/sbin/nologin
gopher:x:13:30:gopher:/var/gopher:/sbin/nologin
ftp:x:14:50:FTP User:/var/ftp:/sbin/nologin
nobody:x:99:99:Nobody:/:/sbin/nologin
saslauth:x:499:499:"Saslauthd user":/var/empty/saslauth:/sbin/nologin
sshd:x:74:74:Privilege-separated SSH:/var/empty/sshd:/sbin/nologin
mailnull:x:47:47::/var/spool/mqueue:/sbin/nologin
smmsp:x:51:51::/var/spool/mqueue:/sbin/nologin
user:x:500:500::/home/user:/bin/bash
```

<p>
</details>

<details>
<summary>
/etc/group
</summary>
<p>

```console
[root@localhost ~]# cat /etc/group
root:x:0:root
bin:x:1:root,bin,daemon
daemon:x:2:root,bin,daemon
sys:x:3:root,bin,adm
adm:x:4:root,adm,daemon
tty:x:5:
disk:x:6:root
lp:x:7:daemon,lp
mem:x:8:
kmem:x:9:
wheel:x:10:root
mail:x:12:mail
uucp:x:14:uucp
man:x:15:
games:x:20:
gopher:x:30:
video:x:39:
dip:x:40:
ftp:x:50:
lock:x:54:
audio:x:63:
nobody:x:99:
users:x:100:
utmp:x:22:
utempter:x:35:
cdrom:x:11:
tape:x:33:
dialout:x:18:
floppy:x:19:
saslauth:x:499:
sshd:x:74:
mailnull:x:47:
smmsp:x:51:
user:x:500:
```

</p>
</details>

Como podemos observar se ha asigando como uid el mínimo especificado en `/etc/login.defs`(500) ya que es el primer usuario creado, se ha creado el directorio /home para `user` y la shell por defecto es `/bin/bash`.

<a name="ejer13"></a>
**Ejercicio 3**. Creación de usuarios
1. Utiliza el manual en línea para leer la sintaxis completa de la utilidad para creación de cuentas y crea dos o tres usuarios en tu sistema cambiando alguno de los valores por defecto.

   Usuario sin directorio home y con contraseña:
   ```console
   [root@localhost ~]# useradd -M nohomeuser -p password
   [root@localhost ~]# ls /home/
   user
   [root@localhost ~]#
   ```

   Usuario con directorio home especifico, guid específico y sin loggin:
   ```console
   [root@localhost ~]# groupadd -g 777 -p safegroup safegroup
   [root@localhost ~]# useradd weirduser -m -d /home/user/weirdhomedir/ -   l -g 777 -p weirduser
   [root@localhost ~]# ls /home/user/             
   weirdhomedir
   [root@localhost ~]#
   ```

2. Elimina alguno de ellos y comprueba que “rastro” ha dejado la cuenta recién eliminada en el sistema.

   ```console
   [root@localhost ~]# userdel weirduser
   [root@localhost ~]# su weirduser
   su: user weirduser does not exist
   [root@localhost ~]# ls /home/user/
   weirdhomedir
   [root@localhost ~]# ls /home/user/weirdhomedir/
   [root@localhost ~]# ls -a /home/user/weirdhomedir/
   .  ..  .bash_logout  .bash_profile  .bashrc
   [root@localhost ~]# ls /home/
   roy user
   [root@localhost ~]# userdel -r roy
   [root@localhost ~]# ls /home/
   user
   [root@localhost ~]#
   ```

   Si no se especifica la opción `-r` el directorio home no se elimina, y por alguna razón no se ha eliminado la entrada en lastlog para weirduser, aunque se especificó en la creación que no se incluyera en dicho log.

   <details>
   <summary>
   lastlog
   </summary>
   <p>

   ```console
   [root@localhost ~]# lastlog
   Username         Port     From             Latest
   root             tty0                      Tue Dec 10 12:42:19 -0500 2019
   bin                                        **Never logged in**
   daemon                                     **Never logged in**
   adm                                        **Never logged in**
   lp                                         **Never logged in**
   sync                                       **Never logged in**
   shutdown                                   **Never logged in**
   halt                                       **Never logged in**
   mail                                       **Never logged in**
   uucp                                       **Never logged in**
   operator                                   **Never logged in**
   games                                      **Never logged in**
   gopher                                     **Never logged in**
   ftp                                        **Never logged in**
   nobody                                     **Never logged in**
   saslauth                                   **Never logged in**
   sshd                                       **Never logged in**
   mailnull                                   **Never logged in**
   smmsp                                      **Never logged in**
   nohomeuser                                 **Never logged in**
   user                                       **Never logged in**
   ```

   </p>
   </details>

3. Entra (orden `su`) en el sistema como uno de estos usuarios que has creado y mira qué archivos tiene en su directorio home. La orden sudo permite cambiar el modo de trabajo a modo root específicamente para ejecutar una orden con privilegios de supervisor y tras su
ejecución continuar con los privilegios del usuario que abrió la sesión.

   ```console
   [root@localhost ~]# su user
   [user@localhost root]$ ls -a ~/
   .  ..  .bash_history  .bash_logout  .bash_profile  .bashrc  weirdhomedir
   [user@localhost root]$ sudo ls
   [sudo] password for user:
   user is not in the sudoers file.  This incident will be reported.
   [user@localhost root]$
   ```

   Para ganar privilegios de administrador editamos `/etc/sudoers` mediante el comando `visudo`, añadiendo la linea:

   ```
   user	ALL=(ALL)	ALL
   ```

   Y ahora podemos ejecutar sudo en el usuario user.

   ```console
   [root@localhost ~]# su user
   [user@localhost root]$ sudo ls -a
   [sudo] password for user:
   .  ..  .bash_history  .bash_logout  .bash_profile  .bashrc  .cshrc  .tcshrc
   [user@localhost root]$
   ```

<a name="ejer14"></a>
**Ejercicio 4**.Visualiza el archivo `/etc/passwd` e indica cual es el formato de cada línea de dicho archivo. Para ello también puedes consultar el man o info de Linux. ¿Quién es el propietario de este archivo y cuáles son sus permisos?

<details>
<summary>
/etc/passwd
</summary>
<p>

```console
[root@localhost ~]# cat /etc/passwd
root:x:0:0:root:/root:/bin/bash
bin:x:1:1:bin:/bin:/sbin/nologin
daemon:x:2:2:daemon:/sbin:/sbin/nologin
adm:x:3:4:adm:/var/adm:/sbin/nologin
lp:x:4:7:lp:/var/spool/lpd:/sbin/nologin
sync:x:5:0:sync:/sbin:/bin/sync
shutdown:x:6:0:shutdown:/sbin:/sbin/shutdown
halt:x:7:0:halt:/sbin:/sbin/halt
mail:x:8:12:mail:/var/spool/mail:/sbin/nologin
uucp:x:10:14:uucp:/var/spool/uucp:/sbin/nologin
operator:x:11:0:operator:/root:/sbin/nologin
games:x:12:100:games:/usr/games:/sbin/nologin
gopher:x:13:30:gopher:/var/gopher:/sbin/nologin
ftp:x:14:50:FTP User:/var/ftp:/sbin/nologin
nobody:x:99:99:Nobody:/:/sbin/nologin
saslauth:x:499:499:"Saslauthd user":/var/empty/saslauth:/sbin/nologin
sshd:x:74:74:Privilege-separated SSH:/var/empty/sshd:/sbin/nologin
mailnull:x:47:47::/var/spool/mqueue:/sbin/nologin
smmsp:x:51:51::/var/spool/mqueue:/sbin/nologin
nohomeuser:x:500:500::/home/nohomeuser:/bin/bash
user:x:501:501::/home/user:/bin/bash
```

</p>
</details>

Formato:

```
user_name:password:UID:GUID:GECOS:directory:shell
```

Permisos y propietario:

```console
[root@localhost ~]# ls -l /etc/passwd
-rw-r--r-- 1 root root 929 Dec 10 13:33 /etc/passwd
[root@localhost ~]#
```

<a name="ejer15"></a>
**Ejercicio 5**. Visualiza el archivo `/etc/shadow` desde un usuario distinto al root ¿Te da algún problema?
¿Sabes por qué? Intenta averiguarlo.

```console
[root@localhost ~]# su user
[user@localhost root]$ cat /etc/shadow
cat: /etc/shadow: Permission denied
[user@localhost root]$ sudo cat /etc/shadow
[sudo] password for user:
root:$6$VObm.HM/$LgYFJgll5YPTZnBkU/3WHHMpWCPd.Q23L2U8YIBJGW0k7nDi2mpJqxR4Wit6zKbUQ.R.lxmJ9eSSGMBY1V7N5.:18240:0:99999:7:::
bin:*:14789:0:99999:7:::
daemon:*:14789:0:99999:7:::
adm:*:14789:0:99999:7:::
lp:*:14789:0:99999:7:::
sync:*:14789:0:99999:7:::
shutdown:*:14789:0:99999:7:::
halt:*:14789:0:99999:7:::
mail:*:14789:0:99999:7:::
uucp:*:14789:0:99999:7:::
operator:*:14789:0:99999:7:::
games:*:14789:0:99999:7:::
gopher:*:14789:0:99999:7:::
ftp:*:14789:0:99999:7:::
nobody:*:14789:0:99999:7:::
saslauth:!!:14916::::::
sshd:!!:14916::::::
mailnull:!!:14916::::::
smmsp:!!:14916::::::
nohomeuser:password:18240:0:99999:7:::
user:$6$zalB6Oa5$pPPCAJi5Dd4C9/1cbfTttkfzjXLOnHX9Dqx2K0sAI1OWRHuLeBGZHwWd2psQeQzcfJnuDkBwDEtijlk9AE/iD/:18240:0:99999:7:::
[user@localhost root]$
```

<a name="ejer16"></a>
**Ejercicio 6**. Creación de grupos
1. Crea un par de grupos y asignáselos a algunos de los usuarios de tu sistema.

   ```console
   [root@localhost ~]# groupadd group1
   [root@localhost ~]# groupadd group2
   [root@localhost ~]# usermod -g group1 user
   [root@localhost ~]# id user
   uid=501(user) gid=778(group1) groups=778(group1)
   [root@localhost ~]# useradd user2
   [root@localhost ~]# usermod -G group2 user2
   [root@localhost ~]# id user2
   uid=502(user2) gid=502(user2) groups=502(user2),779(group2)
   [root@localhost ~]#
   ```

2. ¿Qué información devuelve la orden id si estás conectado como root?

   ```console
   [root@localhost ~]# id
   uid=0(root) gid=777(safegroup) groups=0(root),1(bin),2(daemon),3(sys),4(adm),6(disk),10(wheel),777(safegroup)
   [root@localhost ~]#
   ```

<a name="ejer17"></a>
**Ejercicio 7**. Utilizando la orden (`find`) que ya conoces para la búsqueda de archivos en el sistema de
archivos, anota el nombre absoluto del archivo del kernel de Linux que se ha cargado en
el sistema operativo que estás usando en el laboratorio de prácticas para acceso modo
root.

```console
[x@x ~]$ find / -nowarn -iregex .*fedora.* 2>&1 | grep -v "Permission denied"
```

<details>
<summary>
output
</summary>
<p>

```console
[x@x ~]$ find / -nowarn -iregex .*fedora.* 2>&1 | grep -v "Permission denied"
/tmp/Fedora14-x86-root_fs
/home/zes/Documents/UGR/SO/Fedora14-x86-root_fs.gz
/usr/share/icons/hicolor/scalable/apps/goa-account-fedora.svg
/usr/share/icons/HighContrast/22x22/apps/fedora-release-notes.png
/usr/share/icons/HighContrast/16x16/apps/fedora-release-notes.png
/usr/share/icons/HighContrast/32x32/apps/fedora-release-notes.png
/usr/share/icons/HighContrast/24x24/apps/fedora-release-notes.png
/usr/share/icons/HighContrast/256x256/apps/fedora-release-notes.png
/usr/share/icons/HighContrast/48x48/apps/fedora-release-notes.png
/usr/share/osinfo/os/fedoraproject.org
/usr/share/osinfo/os/fedoraproject.org/fedora-18.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-7.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-15.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-9.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-3.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-25.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-rawhide.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-2.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-24.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-28.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-10.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-19.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-26.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-20.xml
/usr/share/osinfo/os/fedoraproject.org/silverblue-30.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-4.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-22.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-13.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-14.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-16.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-1.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-29.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-12.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-30.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-21.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-8.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-11.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-27.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-17.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-unknown.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-6.xml
/usr/share/osinfo/os/fedoraproject.org/silverblue-28.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-23.xml
/usr/share/osinfo/os/fedoraproject.org/silverblue-29.xml
/usr/share/osinfo/os/fedoraproject.org/fedora-5.xml
/usr/share/osinfo/install-script/fedoraproject.org
/usr/share/osinfo/install-script/fedoraproject.org/fedora-kickstart-desktop.xml
/usr/share/osinfo/install-script/fedoraproject.org/fedora-kickstart-jeos.xml
/usr/share/osinfo/install-script/fedoraproject.org/silverblue-kickstart-desktop.xml
/usr/share/gnome-boxes/osinfo/os/fedoraproject.org
/usr/share/gnome-boxes/osinfo/os/fedoraproject.org/fedora-1.xml
/usr/share/gnome-boxes/osinfo/os/fedoraproject.org/silverblue-28.xml
/usr/lib/gs-plugins-13/libgs_plugin_fedora-pkgdb-collections.so
/usr/lib/gs-plugins-13/libgs_plugin_fedora_langpacks.so
```

</p>
</details>

<a name="ejer18"></a>
**Ejercicio 8**. Un programa que se ejecuta en modo root, ¿dónde podría guardar la información temporal de
forma que ésta se mantuviese entre arranques del sistema?

En `/var`.

<a name="ejer19"></a>
**Ejercicio 9**. Los archivos `/etc/fstab` y `/etc/mtab` muestran información sobre los sistemas de archivos que
se encuentran montados en el sistema. ¿Cuál es la diferencia entre la información que muestra
cada uno de ellos?

El archivo `/etc/fstab` muesta los sistemas de archivos a montar en el arranque del sistema, punto de montaje y propiedades. Mientras que el archivo `/etc/mtab` muestra los sistemas de archivo montados en el sistema, en caso de no montar nada tras el arranque del sistema ambos archivos muestran el mismo contenido, como podemos observar:

<details>
<summary>
contenido
</summary>
<p>

```console
[root@localhost ~]# cat /etc/fstab
#
# /etc/fstab
#
LABEL=ROOT					/		auto	noatime		1 1
tmpfs						/dev/shm	tmpfs	defaults	0 0
tmp						/tmp		tmpfs	rw,mode=1777,fscontext=system_u:object_r:tmp_t:s0	0 0
devpts						/dev/pts	devpts	gid=5,mode=620	0 0
sysfs						/sys		sysfs	defaults	0 0
proc						/proc		proc	defaults	0 0
[root@localhost ~]# cat /etc/mtab  
LABEL=ROOT / auto rw,noatime 0 0
proc /proc proc rw 0 0
sysfs /sys sysfs rw 0 0
devpts /dev/pts devpts rw,gid=5,mode=620 0 0
tmpfs /dev/shm tmpfs rw 0 0
/tmp /tmp tmpfs rw,mode=1777 0 0
none /proc/sys/fs/binfmt_misc binfmt_misc rw 0 0
[root@localhost ~]#
```

</p>
</details>

<a name="ejer110"></a>
**Ejercicio 10**. Edita el archivo `/etc/fstab` del sistema de archivos que estás utilizando en modo root y anota y
describe la información que tiene registrada. Si no conoces alguna opción puedes consultar el
manual en línea: `man fstab`.

Formato:
```console
fs spec : fs file : fs vfstype : fs mntops : fs freq : fs passno
```
<a name="ejer111"></a>
**Ejercicio 11**. Compara la información que contienen los cuatro archivos de texto que se han presentado en
este apartado (`/etc/fstab`, `/etc/mtab`, `/proc/filesystems` y `/proc/mounts`). Describe en un
párrafo para qué te sirve la información que registra cada archivo.

 - `/etc/fstab`, describe la información de los sistemas de archivo a montar en el arranque del sistema.
 - `/etc/mtab`, describe la información de los sistemas de archivos actualmente montados.
 - `/proc/filesystems`, parte del sistema de archivos `procfs`, muestra información de los systemas de archivos activos.
 - `/proc/mounts`, parte del sistema de archivos `procfs`, muestra información sobre los puntos de montaje.



<a name="sesion12"></a>
### Sesión II

---

<a name="modulo2"></a>
## Módulo II

<a name="sesion1"></a>
### Sesión I

<a name="ejer1"></a>
**Ejercicio 1**. ¿Qué hace el siguiente programa? Probad tras la ejecución del programa las siguientes órdenes del shell: `$> cat archivo y $> od -c archivo`

```c
/*
tarea1.c
Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  	/* Primitive system data types for abstraction\
			   of implementation-dependent data types.
			   POSIX Standard: 2.6 Primitive System Data Types
			   <sys/types.h>
			*/
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

char buf1[]="abcdefghij";
char buf2[]="ABCDEFGHIJ";

int main(int argc, char *argv[])
{
int fd;

if( (fd=open("archivo",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0) {
	printf("\nError %d en open",errno);
	perror("\nError en open");
	exit(EXIT_FAILURE);
}
if(write(fd,buf1,10) != 10) {
	perror("\nError en primer write");
	exit(EXIT_FAILURE);
}

if(lseek(fd,40,SEEK_SET) < 0) {
	perror("\nError en lseek");
	exit(EXIT_FAILURE);
}

if(write(fd,buf2,10) != 10) {
	perror("\nError en segundo write");
	exit(EXIT_FAILURE);
}

return EXIT_SUCCESS;
}
```
Primero el programa abre un archivo de nombre *archivo* con los flags `O_CREAT` para crear el archivo en caso de que no exista, `O_TRUNC` para truncar el archivo a longitud 0 en caso de que ya exista, `O_WRONLY` para especificar el modo escritura, `S_IRUSR` y `S_IWUSR` para garantizar permiso de lectura y escritura, respectivamente, al usuario. Imprimiendo por la salida estándar el número de error en caso de error, almacenado en `errno`.

Luego escribimos en el archivo hasta 10B empezando por la posición a la que referencia `buf1`, en caso de que `write()` devuelva un valor distinto de 10 (el número de bytes que queremos escribir) notificamos el error en la salida de error.

Ahora situamos el offset del archivo a 40B desde el inicio del fichero, flag `SEEK_SET`, esta opción nos permite situarnos en una posición mayor a la longitud actual del fichero, que posteriormente si realizamos una escritura, rellenará las posiciones del fichero inexistentes con el carácter nulo `\0`.

Finalmente escribimos el buffer `buff2` en el fichero.

Tras compilar y ejecutar, realizamos la orden `$> cat archivo` y obtenemos la siguiente salida:

```shell
abcdefghijABCDEFGHIJ
```
Con `cat` no se imprimen los caracteres nulos, ya que no son representables en el formato **ASCII**. Si utilizamos la opción `cat -v archivo` obtenemos una *representación* del carácter nulo:

```shell
abcdefghij^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@ABCDEFGHIJ
```

Hacemos un volcado del archivo `$> od -c archivo`, obteniendo:

```shell
0000000   a   b   c   d   e   f   g   h   i   j  \0  \0  \0  \0  \0  \0
0000020  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0
0000040  \0  \0  \0  \0  \0  \0  \0  \0   A   B   C   D   E   F   G   H
0000060   I   J
0000062
```

Y observamos el contenido del archivo en sus distintas posiciones, que corresponden a los 10 primeros bytes de la primera escritura, 30 bytes con el carácter nulo escritos al definir el offset en 40 bytes y la posterior escritura de 10 bytes.

<a name="ejer2"></a>
**Ejercicio 2**. Implementa un programa que realice la siguiente funcionalidad. El programa acepta como argumento el nombre de un archivo (pathname), lo abre y lo lee en bloques de tamaño 80 Bytes, y crea un nuevo archivo de salida, salida.txt, en el que debe aparecer la siguiente información:
```
Bloque 1
// Aquí van los primeros 80 Bytes del archivo pasado como argumento.

Bloque 2
// Aquí van los siguientes 80 Bytes del archivo pasado como argumento.

...

Bloque n
// Aquí van los siguientes 80 Bytes del archivo pasado como argumento.
```
Si no se pasa un argumento al programa se debe utilizar la entrada estándar como archivo de entrada.

Solución:
```c
/*
ejercicio2.c
*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include <string.h>

#define BLOCK_SIZE 80
char buf[BLOCK_SIZE];
int read_blocks(int);

int main(int argc, char *argv[]){
  int fd;
  int std_read = 1;
  if(argc == 1){
    printf("Se ha seleccionado la entrada estándar como archivo de entrada\n");
    fd = STDIN_FILENO;
    read_blocks(fd);
  }
  else{
    if(argc == 2){
      if( (fd=open(argv[1], O_RDONLY)) < 0){
        printf("\nError %d en open",errno);
        perror("\nError en open");
        exit(EXIT_FAILURE);
      }

      read_blocks(fd);
      if(close(fd) < 0){
        printf("\nError %d en close",errno);
        perror("\nError en close");
        exit(EXIT_FAILURE);
      }
    }
    else{
      printf("\nError, invalid number of arguments\nUso: ejercicio2 [pathname_to_file]");
      exit(EXIT_FAILURE);
    }
  }

  return EXIT_SUCCESS;
}

void close_fd(int fd){
  if(close(fd) < 0){
    printf("\nError %d en close",errno);
    perror("\nError en close");
    exit(EXIT_FAILURE);
  }
}

int read_blocks(int fd){

  int count;
  int eof = 0;
  int fd_out;
  if((fd_out=open("salida.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0) {
    printf("\nError %d en open fd_out",errno);
    perror("\nError en open");
    exit(EXIT_FAILURE);
  }

  for(int i = 1; !eof; ++i){
    count = 0;
    count = read(fd, buf, BLOCK_SIZE);
    char buf_w[BLOCK_SIZE+20];
    if(count < 0){
      printf("\nError %d en read",errno);
      perror("\nError en read");
      close_fd(fd_out);
      exit(EXIT_FAILURE);
    }else{
      sprintf(buf_w, "Bloque %i\n%.*s\n", i, count, buf);
      if(write(fd_out, buf_w, strlen(buf_w)) < 0){
        printf("\nError %d en write",errno);
        perror("\nError en write");
        close_fd(fd_out);
        exit(EXIT_FAILURE);
      }

      if(count < BLOCK_SIZE)eof=1;
    }
  }

  close_fd(fd_out);
  return EXIT_SUCCESS;
}
```
**Modificación adicional**. ¿Cómo tendrías que modificar el programa para que una vez finalizada la escritura en el archivo de salida y antes de cerrarlo, pudiésemos indicar en su primera línea el número de etiquetas ''Bloque i'' escritas de forma que tuviese la siguiente apariencia?:

```
El número de bloques es <nº_bloques>  
Bloque 1  
// Aquí van los primeros 80 Bytes del archivo pasado como argumento.  
Bloque 2  
// Aquí van los siguientes 80 Bytes del archivo pasado como argumento.  
...
```
Situando el `offset` mediante `lseek` al inicio, leemos y copiamos todo el contenido del archivo (cambiamos el flag `O_WRONLY` por `O_RDWR`), y escribimos el número de bloques (sacamos el contador `i` fuera del bucle) y volvemos a escribir todo el contenido copiado.

Solución:

```c
int sfd = lseek(fd_out, 0, SEEK_END);

lseek(fd_out, 0, SEEK_SET);
char file_copy[sfd];
read(fd_out, file_copy, sfd);
lseek(fd_out, 0, SEEK_SET);


sprintf(buf_w, "El número de bloques es %i\n", i-1);
if(write(fd_out, buf_w, strlen(buf_w)) < 0){
  printf("\nError %d en write",errno);
  perror("\nError en write");
  close_fd(fd_out);
  exit(EXIT_FAILURE);
}
if(write(fd_out, file_copy, sfd) < 0){
  printf("\nError %d en write",errno);
  perror("\nError en write");
  close_fd(fd_out);
  exit(EXIT_FAILURE);
}

```

<a name="ejer3"></a>
**Ejercicio 3**. ¿Qué hace el siguiente programa?

```c
/*
tarea2.c
Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
*/

#include<unistd.h>  /* POSIX Standard: 2.10 Symbolic Constants <unistd.h>
		     */
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  /* Primitive system data types for abstraction	\
			   of implementation-dependent data types.
			   POSIX Standard: 2.6 Primitive System Data Types
			   <sys/types.h>
		       */
#include<sys/stat.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

int main(int argc, char *argv[])
{
int i;
struct stat atributos;
char tipoArchivo[30];

if(argc<2) {
	printf("\nSintaxis de ejecucion: tarea2 [<nombre_archivo>]+\n\n");
	exit(EXIT_FAILURE);
}
for(i=1;i<argc;i++) {
	printf("%s: ", argv[i]);
	if(lstat(argv[i],&atributos) < 0) {
		printf("\nError al intentar acceder a los atributos de %s",argv[i]);
		perror("\nError en lstat");
	}
	else {
		if(S_ISREG(atributos.st_mode)) strcpy(tipoArchivo,"Regular");
		else if(S_ISDIR(atributos.st_mode)) strcpy(tipoArchivo,"Directorio");
		else if(S_ISCHR(atributos.st_mode)) strcpy(tipoArchivo,"Especial de caracteres");
		else if(S_ISBLK(atributos.st_mode)) strcpy(tipoArchivo,"Especial de bloques");
		else if(S_ISFIFO(atributos.st_mode)) strcpy(tipoArchivo,"Tuberia con nombre (FIFO)");
		else if(S_ISLNK(atributos.st_mode)) strcpy(tipoArchivo,"Enlace relativo (soft)");
		else if(S_ISSOCK(atributos.st_mode)) strcpy(tipoArchivo,"Socket");
		else strcpy(tipoArchivo,"Tipo de archivo desconocido");
		printf("%s\n",tipoArchivo);
	}
}

return EXIT_SUCCESS;
}
```

Muestra por la salida estandar el tipo de archivo para cada archivo pasado por parámetro.


<a name="ejer4"></a>
**Ejercicio 4**. Define una macro en lenguaje C que tenga la misma funcionalidad que la macro S_ISREG(mode) usando para ello los flags definidos en <sys/stat.h> para el campo st_mode de la struct stat, y comprueba que funciona en un programa simple. Consulta en un libro de C o en internet cómo se especifica una macro con argumento en C.

```c
#define S_ISREG2(mode)
...
```
Solución:
```c
#define S_ISREG2(mode)  (((mode_t)(mode) & S_IFREG ) ? 1 : 0)
```

---

<a name="sesion2"></a>
### Sesión II

<a name="ejer21"></a>
**Ejercicio 1**. ¿Qué hace el siguiente programa?

```c
/*
tarea3.c
Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
Este programa fuente est� pensado para que se cree primero un programa con la parte
 de CREACION DE ARCHIVOS y se haga un ls -l para fijarnos en los permisos y entender
 la llamada umask.
En segundo lugar (una vez creados los archivos) hay que crear un segundo programa
 con la parte de CAMBIO DE PERMISOS para comprender el cambio de permisos relativo
 a los permisos que actualmente tiene un archivo frente a un establecimiento de permisos
 absoluto.
*/

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>		//Needed for open
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
int fd1,fd2;
struct stat atributos;

//CREACION DE ARCHIVOS
if( (fd1=open("archivo1",O_CREAT|O_TRUNC|O_WRONLY,S_IRGRP|S_IWGRP|S_IXGRP))<0) {
	printf("\nError %d en open(archivo1,...)",errno);
	perror("\nError en open");
	exit(EXIT_FAILURE);
}

umask(0);
if( (fd2=open("archivo2",O_CREAT|O_TRUNC|O_WRONLY,S_IRGRP|S_IWGRP|S_IXGRP))<0) {
	printf("\nError %d en open(archivo2,...)",errno);
	perror("\nError en open");
	exit(EXIT_FAILURE);
}

//CAMBIO DE PERMISOS
if(stat("archivo1",&atributos) < 0) {
	printf("\nError al intentar acceder a los atributos de archivo1");
	perror("\nError en lstat");
	exit(EXIT_FAILURE);
}
if(chmod("archivo1", (atributos.st_mode & ~S_IXGRP) | S_ISGID) < 0) {
	perror("\nError en chmod para archivo1");
	exit(EXIT_FAILURE);
}
if(chmod("archivo2",S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH) < 0) {
	perror("\nError en chmod para archivo2");
	exit(EXIT_FAILURE);
}

return EXIT_SUCCESS;
}
```
El programa crea dos archivos, asignando permisos de lectura, escritura y ejecución al grupo, seguidamente se leen los atributos del `archivo1`, se desactiva el permiso de ejecución para el grupo y se activa el *Sticky bit*, mientras que al `archivo2` se le asignan los permisos `rwx` al usuario, `rw` al grupo y `r` a otros.
Con la llamada `umask(0)` especificamos que cualquier permiso puede ser modificado.

<a name="ejer22"></a>
**Ejercicio 2**.Realiza un programa en C utilizando las llamadas al sistema necesarias que acepte como entrada:

- Un argumento que representa el 'pathname' de un directorio.
- Otro argumento que es un número octal de 4 dígitos (similar al que se puede utilizar para cambiar los permisos en la llamada al sistema chmod). Para convertir este argumento tipo cadena a un tipo numérico puedes utilizar la función strtol. Consulta el manual en línea para conocer sus argumentos.

El programa tiene que usar el número octal indicado en el segundo argumento para cambiar los permisos de todos los archivos que se encuentren en el directorio indicado en el primer argumento.  
El programa debe proporcionar en la salida estándar una línea para cada archivo del directorio que esté formada por:  
```shell
<nombre_de_archivo> : <permisos_antiguos> <permisos_nuevos>
```
Si no se pueden cambiar los permisos de un determinado archivo se debe especificar la siguiente información en la línea de salida:  
```shell
<nombre_de_archivo> : <errno> <permisos_antiguos>
```

Solución:
```c
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>

void closedir_safe(DIR*);

int main(int argc, char *argv[]){
  size_t name_len = strlen(argv[0])-2;
  char name[name_len];
  char *name_p = &argv[0][2];
  sprintf(name,"%.*s", (int)name_len, name_p);

  if(argc != 3){
    printf("Sintaxis de ejecucion: %s <nombre_directorio> <mascara_octal_4d>\n\n"
    , argv[0]);

    exit(EXIT_FAILURE);
  }

  long int mask;
  if((mask=strtol(argv[2], (char**)NULL, 8)) == 0 && argv[2] != 0 ){
    printf("Error %d en strtol(%s)\n",errno, argv[2]);
    perror("Error en strtol\n");
    exit(EXIT_FAILURE);
  }
  //printf("mask: %li\n", mask);

  DIR* dir;

  if( (dir=opendir(argv[1])) == NULL ){
    printf("Error %d en opendir(%s)\n",errno, argv[1]);
    perror("Error en opendir\n");
    exit(EXIT_FAILURE);
  }

  struct dirent *dirp;
  struct stat attr;
  unsigned int permisos_antiguos;

  int i = 0;
  for(errno = 0; (dirp=readdir(dir)) != NULL; errno = 0, ++i){
    if(errno != 0){
      printf("Error %d en readdir\n",errno);
      perror("Error en readdir\n");
      exit(EXIT_FAILURE);
    }

    if( strcmp(dirp->d_name, ".")!=0 && strcmp(dirp->d_name, "..")!=0 && strcmp(dirp->d_name, name)!=0){
      if(lstat(dirp->d_name, &attr) < 0){
        printf("Error %d al intentar acceder a los atributos de %s\n", errno, dirp->d_name);
        perror("Error en lstat\n");
      }else{
        permisos_antiguos = ((attr.st_mode & S_IRUSR)|(attr.st_mode & S_IWUSR)|(attr.st_mode & S_IXUSR)|/*owner*/
        (attr.st_mode & S_IRGRP)|(attr.st_mode & S_IWGRP)|(attr.st_mode & S_IXGRP)|/*group*/
        (attr.st_mode & S_IROTH)|(attr.st_mode & S_IWOTH)|(attr.st_mode & S_IXOTH));/*other*/
        if( chmod(dirp->d_name, mask) < 0 ){
          printf("Error %d en chmod para %s\n", errno, dirp->d_name);
          printf("%s : <%d> <%.4o>\n", dirp->d_name, errno, permisos_antiguos);
        }else{
          printf("%s : <%.4o> <%.4o>\n", dirp->d_name, permisos_antiguos, (unsigned int)mask);
        }
      }
    }

  }


  closedir_safe(dir);
  return EXIT_SUCCESS;
}

void closedir_safe(DIR* dir){
  if(closedir(dir) < 0){
    printf("Error %d en closedir\n",errno);
    perror("Error en closedir\n");
    exit(EXIT_FAILURE);
  }
}
```
<a name="ejer23"></a>
**Ejercicio 3**. Programa una nueva orden que recorra la jerarquía de subdirectorios existentes a partir de uno dado como argumento y devuelva la cuenta de todos aquellos archivos regulares que tengan permiso de ejecución para el grupo y para otros. Además del nombre de los archivos encontrados, deberá devolver sus números de inodo y la suma total de espacio ocupado por dichos archivos. El formato de la nueva orden será:
```shell
$ ./buscar <pathname>
```
Donde `<pathname>` especifica la ruta del directorio a partir del cual queremos que empiece a analizar la estructura del árbol de subdirectorios. En caso de que no se le de argumento, tomará como punto de partida el directorio actual. Ejemplo de la salida después de ejecutar el programa:
```shell
Los i-nodos son:
./a.out 55
./bin/ej 123
./bin/ej2 87
...
Existen 24 archivos regulares con permiso x para grupo y otros
El tamaño total ocupado por dichos archivos es 2345674 bytes
```

Solución:
```c
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<unistd.h>
#include <limits.h>

void closedir_safe(DIR *);
DIR* opendir_safe(char*);

struct file_cont{
  unsigned int n;
  off_t st_size;
};

void buscar_recursivo(char*, struct file_cont *);

int main(int argc, char* argv[]){
  char path[PATH_MAX];
  if(argc > 2){
    printf("Uso: %s [<path_name/>]\n", argv[0]);
    exit(EXIT_FAILURE);
  }else{
    if(argc == 1){
      if( (getcwd(path, PATH_MAX)) == NULL ){
        printf("Error %d en getcwd()\n", errno);
        perror("Error en getcwd()\n");
        exit(EXIT_FAILURE);
      }
      strcat(path, "/");
    }else{
      strcpy(path, argv[1]);
    }
  }

  printf("%s\n", path);

  struct file_cont fcont;
  fcont.n = 0;
  fcont.st_size = 0;

  printf("Los i-nodos son:\n");
  buscar_recursivo(path, &fcont);
  printf("Existen %u archivos regulares con permiso x para grupo y otros\n", fcont.n);
  printf("El tamaño total ocupado por dichos archivos es %lu bytes\n", fcont.st_size);

  return EXIT_SUCCESS;
}

void buscar_recursivo(char *path, struct file_cont *fcont){
  DIR *dir;
  if( (dir=opendir_safe(path)) != NULL){

    int i = 0;
    struct dirent *dirp;
    struct stat attr;

    for(errno = 0; (dirp=readdir(dir)) != NULL; errno=0, ++i){
      if(errno != 0){
        printf("Error %d en readdir\n",errno);
        perror("Error en readdir\n");
        closedir_safe(dir);
        exit(EXIT_FAILURE);
      }

      char dirp_name_path[PATH_MAX];
      strcpy(dirp_name_path, path);
      strcat(dirp_name_path, dirp->d_name);

      if( strcmp(dirp->d_name, ".")!=0 && strcmp(dirp->d_name, "..")!=0){
        if(lstat(dirp_name_path, &attr) < 0){
          printf("Error %d al intentar acceder a los atributos de %s\n", errno, dirp->d_name);
          perror("Error en lstat\n");
        }else{
          if(S_ISREG(attr.st_mode) && (attr.st_mode & S_IXGRP)!=0 && (attr.st_mode & S_IXOTH)!=0 ){
            printf("%s  %lu\n",  dirp_name_path, attr.st_ino);
            fcont->n += 1;
            fcont->st_size += attr.st_size;
          }else{
            if(S_ISDIR(attr.st_mode)){
              strcat(dirp_name_path, "/");
              buscar_recursivo(dirp_name_path, fcont);
            }
          }
        }
      }
    }
    closedir_safe(dir);
  }
}


DIR* opendir_safe(char *path){
  DIR* dir;
  if( (dir=opendir(path)) == NULL){
    printf("Error %d en opendir(%s)\n", errno, path);
    perror("Error en opendir\n");
    return (DIR *)NULL;
  }

  return dir;
}

void closedir_safe(DIR *dir){
  if( (closedir(dir)) < 0){
    printf("Error %d en closedir\n",errno);
    perror("Error en closedir\n");
    exit(EXIT_FAILURE);
  }
}
```
<a name="ejer24"></a>
**Ejercicio 4**. Implementa de nuevo el programa buscar del ejercicio 3 utilizando la llamada al sistema nftw.

Solución:

```c
#define _XOPEN_SOURCE 500
#include<ftw.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<limits.h>

struct file_cont{
  unsigned int n;
  off_t st_size;
}global_fcont;

int buscar(const char*, const struct stat*, int, struct FTW*);

int main(int argc, char *argv[]){

  char path[PATH_MAX];

  if(argc > 2){
    printf("Uso: %s [<path_name/>]\n", argv[0]);
    exit(EXIT_FAILURE);
  }else{
    if(argc == 1){
      if( (getcwd(path, PATH_MAX)) == NULL ){
        printf("Error %d en getcwd()\n", errno);
        perror("Error en getcwd()\n");
        exit(EXIT_FAILURE);
      }
      strcat(path, "/");
    }else{
      strcpy(path, argv[1]);
    }
  }

  printf("%s\n", path);

  struct file_cont *fcont = &global_fcont;
  fcont->n=0;
  fcont->st_size=0;

  printf("Los i-nodos son:\n");
  if( (nftw(path, buscar, 10, 0)) != 0){
    perror("Error en nftw()\n");
    exit(EXIT_FAILURE);
  }
  printf("Existen %u archivos regulares con permiso x para grupo y otros\n", fcont->n);
  printf("El tamaño total ocupado por dichos archivos es %lu bytes\n", fcont->st_size);

  return EXIT_SUCCESS;
}

int buscar(const char* path, const struct stat* stat, int flags, struct FTW* ftw){
  struct file_cont *fcont = &global_fcont;
  if((flags & FTW_D)==0){
    if(S_ISREG(stat->st_mode) && (stat->st_mode & S_IXGRP)!=0 && (stat->st_mode & S_IXOTH)!=0 ){
      printf("%s  %lu\n",  path, stat->st_ino);
      fcont->n += 1;
      fcont->st_size += stat->st_size;
    }
  }
  return 0;
}
```

---

<a name="sesion3"></a>
### Sesión3

<a name="ejer31"></a>
**Ejercicio 1**. Implementa un programa en C que tenga como argumento un número entero. Este programa debe crear un proceso hijo que se encargará de comprobar si dicho número es un número par o impar e informará al usuario con un mensaje que se enviará por la salida estándar. A su vez, el proceso padre comprobará si dicho número es divisible por 4, e informará si lo es o no usando igualmente la salida estándar.

Solución:
```c
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include<errno.h>
#include<stdlib.h>

int _multiplo_4(long int n){
  if(n % 4 == 0){
    return 1;
  }else{
    return 0;
  }
}

int _par(long int n){
  if(n % 2 == 0){
    return 1;
  }else{
    return 0;
  }
}

int main(int argc, char *argv[]){

  if(argc != 2){
    printf("Uso: %s <long_int>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  long int n;

  if( (n=strtol(argv[1], (char**)NULL, 10)) == 0 && errno != 0 ){
    printf("Error %d en strtol(%s)\n",errno, argv[1]);
    perror("Error en strtol\n");
    exit(EXIT_FAILURE);
  }
  printf("El numero %li:\n", n);

  pid_t pid;
  pid=fork();

  if(pid==0){
    if(_par(n)){
      printf("(%i) es par\n", pid);
    }else{
      printf("(%i) es impar\n", pid);
    }
  }else{
    if(_multiplo_4(n)){
      printf("(%i) es multiplo de 4\n", pid);
    }else{
      printf("(%i) no es multiplo de 4\n", pid);
    }
  }

  return EXIT_SUCCESS;
}
```
<a name="ejer32"></a>
**Ejercicio 2**. ¿Qué hace el siguiente programa? Intenta entender lo que ocurre con las variables y sobre todo con los mensajes por pantalla cuando el núcleo tiene activado/desactivado el mecanismo de buffering.

```c
//tarea4.c
//Trabajo con llamadas al sistema del Subsistema de Procesos "POSIX 2.10 compliant"
//Prueba el programa tal y como está. Después, elimina los comentarios (1) y pruebalo de nuevo.

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

int global=6;
char buf[]="cualquier mensaje de salida\n";

int main(int argc, char *argv[])
{
int var;
pid_t pid;

var=88;
if(write(STDOUT_FILENO,buf,sizeof(buf)+1) != sizeof(buf)+1) {
	perror("\nError en write");
	exit(EXIT_FAILURE);
}
//(1)if(setvbuf(stdout,NULL,_IONBF,0)) {
//	perror("\nError en setvbuf");
//}
printf("\nMensaje previo a la ejecución de fork");

if( (pid=fork())<0) {
	perror("\nError en el fork");
	exit(EXIT_FAILURE);
}
else if(pid==0) {  
	//proceso hijo ejecutando el programa
	global++;
	var++;
} else  //proceso padre ejecutando el programa
	sleep(1);		
printf("\npid= %d, global= %d, var= %d\n", getpid(),global,var);
exit(EXIT_SUCCESS);
}

```

Aunque `write()` no cree un buffer de salida, el núcleo si lo crea para las operaciones de I/O en c, en este caso la función `printf()`, lo que provoca que con la llamada a `fork()` se duplique dicho buffer, impriendo dos veces *Mensaje previo a la ejecución de fork*, con la llamada a `setvbuf()` desactivamos el buffering en las operaciones I/O de la biblioteca estándar, imprimiendo el mensaje solo una vez, antes del `fork()`.

<a name="ejer33"></a>
**Ejercicio 3**. Indica qué tipo de jerarquías de procesos se generan mediante la ejecución de cada uno de los siguientes fragmentos de código. Comprueba tu solución implementando un código para generar 20 procesos en cada caso, en donde cada proceso imprima su PID y el del padre, PPID.

```c
/*
Jerarquía de procesos tipo 2
*/
for (i=1; i < nprocs; i++) {
 if ((childpid= fork()) == -1) {
 fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
 exit(-1);
 }

 if (childpid)
 break;
}
/*
Jerarquía de procesos tipo 1
*/
for (i=1; i < nprocs; i++) {
 if ((childpid= fork()) == -1) {
 fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
 exit(-1);
 }

 if (!childpid)
 break;
}
```

Solución jerarquía tipo 1:
```c
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

#define MAX_CHILD 10

int main(int argc, char *argv[]){

  //Jerarquia tipo 1(el padre crea todos los hijos)

  pid_t pid;
  for(unsigned int i = 0; (i < MAX_CHILD) && (pid=fork()) != 0 ; ++i){

    if(pid == -1){
      printf("Error %d en fork() %i\n", errno, i);
      perror("Error en fork()\n");
      exit(EXIT_FAILURE);
    }
  }

  printf("PID %u, PPID %u\n", getpid(), getppid());
  return EXIT_SUCCESS;
}
```

Solución jerarquía tipo 2:
```c
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

#define MAX_CHILD 10

int main(int argc, char *argv[]){

  //Jerarquia tipo 2(solo el proceso sin hijo crea un hijo)

  pid_t pid;
  for(unsigned int i = 0; (i < MAX_CHILD) && (pid=fork()) == 0 ; ++i){

    if(pid == -1){
      printf("Error %d en fork() %i\n", errno, i);
      perror("Error en fork()\n");
      exit(EXIT_FAILURE);
    }
  }

  printf("PID %u, PPID %u\n", getpid(), getppid());
  return EXIT_SUCCESS;
}
```

<a name="ejer34"></a>
**Ejercicio 4**. Implementa un programa que lance cinco procesos hijo. Cada uno de ellos se identificará en la salida estándar, mostrando un mensaje del tipo `Soy el hijo PID`. El proceso padre simplemente tendrá que esperar la finalización de todos sus hijos y cada vez que detecte la finalización de uno de sus hijos escribirá en la salida estándar un mensaje del tipo:
```shell
Acaba de finalizar mi hijo con <PID>
Sólo me quedan <NUM_HIJOS> hijos vivos
```

Solución:
```c
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>
#include <sys/wait.h>

#define HIJOS_MAX 5

int main(int argc, char *argv[]){

  unsigned int n_hijos = 0;
  pid_t lastchild;

  do{
    if( (lastchild=fork()) < 0){
      printf("Error %d en fork() %i\n", errno, n_hijos);
      perror("Error en fork()\n");
      exit(EXIT_FAILURE);
    }

    if(lastchild==0){
      printf("Soy el hijo %u\n", getpid());
    }else{
      ++n_hijos;
    }
  }while(n_hijos < HIJOS_MAX && lastchild != 0);

  if(lastchild==0){
    exit(EXIT_SUCCESS);
  }else{
    int waitstatus;
    do{
      if( (lastchild=wait(&waitstatus)) < 0){
        printf("Error %d en wait()\n", errno);
        perror("Error en wait()\n");
        exit(EXIT_FAILURE);
      }else{
        --n_hijos;
        printf("Acaba de finalizar mi hijo %u\n", lastchild);
        printf("Sólo me quedan %u hijos vivos\n", n_hijos);
      }
    }while(n_hijos > 0);
  }

  return EXIT_SUCCESS;
}
```
<a name="ejer35"></a>
**Ejercicio 5**.Implementa una modificación sobre el anterior programa en la que el proceso padre espera primero a los hijos creados en orden impar (1º,3º,5º) y después a los hijos pares (2º y 4º).

Solución:

```c
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>
#include <sys/wait.h>

#define HIJOS_MAX 5

int main(int argc, char *argv[]){

  unsigned int n_hijos = 0;
  pid_t lastchild;
  pid_t hijos[HIJOS_MAX];

  do{
    if( (lastchild=fork()) < 0){
      printf("Error %d en fork() %i\n", errno, n_hijos);
      perror("Error en fork()\n");
      exit(EXIT_FAILURE);
    }

    if(lastchild==0){
      printf("Soy el hijo %u\n", getpid());
    }else{
      hijos[n_hijos]=lastchild;
      ++n_hijos;
    }
  }while(n_hijos < HIJOS_MAX && lastchild != 0);

  if(lastchild==0){
    exit(EXIT_SUCCESS);
  }else{
    int waitstatus;
    //Hijos impares(0, 2, 4)
      if( (lastchild=waitpid(hijos[0], &waitstatus, 0)) < 0){
        printf("Error %d en wait()\n", errno);
        perror("Error en wait()\n");
        exit(EXIT_FAILURE);
      }else{
        if(lastchild > 0){
          --n_hijos;
          printf("Acaba de finalizar mi hijo %u (1)\n", lastchild);
          printf("Sólo me quedan %u hijos vivos\n", n_hijos);
        }
      }

      if( (lastchild=waitpid(hijos[2], &waitstatus, 0)) < 0){
        printf("Error %d en wait()\n", errno);
        perror("Error en wait()\n");
        exit(EXIT_FAILURE);
      }else{
        if(lastchild > 0){
          --n_hijos;
          printf("Acaba de finalizar mi hijo %u (3)\n", lastchild);
          printf("Sólo me quedan %u hijos vivos\n", n_hijos);
        }
      }

      if( (lastchild=waitpid(hijos[4], &waitstatus, 0)) < 0){
        printf("Error %d en wait()\n", errno);
        perror("Error en wait()\n");
        exit(EXIT_FAILURE);
      }else{
        if(lastchild > 0){
          --n_hijos;
          printf("Acaba de finalizar mi hijo %u (5)\n", lastchild);
          printf("Sólo me quedan %u hijos vivos\n", n_hijos);
        }
      }

    do{ //Hijos pares(resto)
      if( (lastchild=wait(&waitstatus)) < 0){
        printf("Error %d en wait()\n", errno);
        perror("Error en wait()\n");
        exit(EXIT_FAILURE);
      }else{
        --n_hijos;
        printf("Acaba de finalizar mi hijo %u\n", lastchild);
        printf("Sólo me quedan %u hijos vivos\n", n_hijos);
      }
    }while(n_hijos > 0);
  }

  return EXIT_SUCCESS;
}
```

<a name="ejer36"></a>
**Ejercicio 6**.¿Qué hace el siguiente programa?
```c
//tarea5.c
//Trabajo con llamadas al sistema del Subsistema de Procesos conforme a POSIX 2.10

#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
pid_t pid;
int estado;

if( (pid=fork())<0) {
	perror("\nError en el fork");
	exit(EXIT_FAILURE);
}
else if(pid==0) {  //proceso hijo ejecutando el programa
	if( (execl("/usr/bin/ldd","ldd","./tarea5")<0)) {
		perror("\nError en el execl");
		exit(EXIT_FAILURE);
	}
}
wait(&estado);
/*
<estado> mantiene información codificada a nivel de bit sobre el motivo de
finalización del proceso hijo que puede ser el número de señal o 0 si alcanzó su
finalización normalmente. Mediante la variable estado de wait(), el proceso
padre recupera el valor especificado por el proceso hijo como argumento de la
llamada exit(), pero desplazado 1 byte porque el sistema incluye en el byte
menos significativo el código de la señal que puede estar asociada a la
terminación del hijo. Por eso se utiliza estado>>8 de forma que obtenemos el
valor del argumento del exit() del hijo.
*/

printf("\nMi hijo %d ha finalizado con el estado %d\n",pid,estado>>8);

exit(EXIT_SUCCESS);

}
```

El programa crea un hijo y este ejecuta el comando `ldd` sobre el propio ejecutable `./tarea5`.

<a name="ejer37"></a>
**Ejercicio 7**.Escribe un programa que acepte como argumentos el nombre de un programa, sus argumentos si los tiene, y opcionalmente la cadena *bg*. Nuesto programa deberá ejecutar el programa pasado como primer argumento en foreground si no se especifica la cadena *bg* y en background en caso contrario. Si el programa tiene argumentos hay que ejecutarlo con éstos.

Solución:
```c
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[]){

  if(argc < 2){
    printf("Uso: %s <path_programa> [<program_name>...<argumento_n>] [<bg>]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int bg=0;
  if(strcmp(argv[argc-1], "bg") == 0){
    bg=1;
    printf("Background option detected\n" );
  }

  int err_exec;
  char *params[argc-1];

  if(bg){
    for(int i = 0; i < argc-3; ++i){
      params[i]=argv[i+2];
    }

    params[argc-3] = "&";
  }else{
    for(int i = 0; i < argc-2; ++i){
      params[i] = argv[i+2];
    }
  }

  params[argc-2]=(char*)NULL;



  if( (err_exec=execv(argv[1], params)) < 0){
    printf("Error %d en execv()\n", errno);
    perror("Error en execl()\n");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
```

---

<a name="sesion4"></a>
### Sesión 4

<a name="ejer41"></a>
**Ejercicio 1**. Consulte en el manual las llamadas al sistema para la creación de archivos especiales en general `mknod` y la específica para archivos *FIFO* `mkfifo`. Pruebe a ejecutar el siguiente código correspondiente a dos programas que modelan el problema del *productor/consumidor*, los cuales utilizan como mecanismo de comunicación un cauce *FIFO*. Determine en qué orden y manera se han de ejecutar los dos programas para su correcto funcionamiento y cómo queda reflejado en el sistema que estamos utilizando un cauce *FIFO*. Justifique la respuesta.

Productor:
```c
//productorFIFO.c
//Productor que usa mecanismo de comunicacion FIFO

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#define ARCHIVO_FIFO "ComunicacionFIFO"

int main(int argc, char *argv[])
{
int fd;

//Comprobar el uso correcto del programa
if(argc != 2) {
printf("\nproductorFIFO: faltan argumentos (mensaje)");
printf("\nPruebe: productorFIFO <mensaje>, donde <mensaje> es una cadena de caracteres.\n");
exit(EXIT_FAILURE);
}

//Intentar abrir para escritura el cauce FIFO
if( (fd=open(ARCHIVO_FIFO,O_WRONLY)) <0) {
perror("\nError en open");
exit(EXIT_FAILURE);
}

//Escribir en el cauce FIFO el mensaje introducido como argumento
if( (write(fd,argv[1],strlen(argv[1])+1)) != strlen(argv[1])+1) {
perror("\nError al escribir en el FIFO");
exit(EXIT_FAILURE);
}

close(fd);
return EXIT_SUCCESS;
}
```

Consumidor:
```c
//consumidorFIFO.c
//Consumidor que usa mecanismo de comunicacion FIFO.

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define ARCHIVO_FIFO "ComunicacionFIFO"

int main(void)
{
int fd;
char buffer[80];// Almacenamiento del mensaje del cliente.
int leidos;

//Crear el cauce con nombre (FIFO) si no existe
umask(0);
mknod(ARCHIVO_FIFO,S_IFIFO|0666,0);
//tambi�n vale: mkfifo(ARCHIVO_FIFO,0666);

//Abrir el cauce para lectura-escritura
if ( (fd=open(ARCHIVO_FIFO,O_RDWR)) <0) {
perror("open");
exit(EXIT_FAILURE);
}

//Aceptar datos a consumir hasta que se env�e la cadena fin
while(1) {
leidos=read(fd,buffer,80);
if(strcmp(buffer,"fin")==0) {
close(fd);
return EXIT_SUCCESS;
}
printf("\nMensaje recibido: %s\n", buffer);
}

return EXIT_SUCCESS;
}
```

El programa consumidor primero establece la máscara de permisos para porder habilitar cualquier permiso `umask(0)`, seguidamente crea el cauce *FIFO* mediante `mknod(ARCHIVO_FIFO,S_IFIFO|0666,0)` y lo abre, entra en el bucle quedando bloqueado hasta que el programa *productor* escriba en el cauce mediante `(write(fd,argv[1],strlen(argv[1])+1)) != strlen(argv[1])+1`, abriendo dicho cauce anteriormente mediante `(fd=open(ARCHIVO_FIFO,O_WRONLY))`.

<a name="ejer42"></a>
**Ejercicio 2**.Consulte en el manual en línea la llamada al sistema pipe para la creación de cauces sin nombre. Pruebe a ejecutar el siguiente programa que utiliza un cauce sin nombre y describa la función que realiza. Justifique la respuesta.

```c
/*
tarea6.c
Trabajo con llamadas al sistema del Subsistema de Procesos y Cauces conforme a POSIX 2.10
*/

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

int main(int argc, char *argv[])
{
int fd[2], numBytes;
pid_t PID;
char mensaje[]= "\nEl primer mensaje transmitido por un cauce!!\n";
char buffer[80];

pipe(fd); // Llamada al sistema para crear un cauce sin nombre

if ( (PID= fork())<0) {
	perror("fork");
	exit(EXIT_FAILURE);
}
if (PID == 0) {
	//Cierre del descriptor de lectura en el proceso hijo
	close(fd[0]);
	// Enviar el mensaje a traves del cauce usando el descriptor de escritura
	write(fd[1],mensaje,strlen(mensaje)+1);
	exit(EXIT_SUCCESS);
}
else { // Estoy en el proceso padre porque PID != 0
	//Cerrar el descriptor de escritura en el proceso padre
	close(fd[1]);
	//Leer datos desde el cauce.
	numBytes= read(fd[0],buffer,sizeof(buffer));
	printf("\nEl numero de bytes recibidos es: %d",numBytes);
	printf("\nLa cadena enviada a traves del cauce es: %s", buffer);
}

return EXIT_SUCCESS;
}
```

Se crea un cauce sin nombre, se crea un proceso hijo que hereda los descriptores del cauce y se cierra el descriptor de lectura en el proceso hijo y el descriptor de escritura en el proceso padre, el hijo escribe el mensaje y el padre lo lee y lo imprime por la salida estándar.

<a name="ejer43"></a>
**Ejercicio 3**. Redirigiendo las entradas y salidas estándares de los procesos a los cauces podemos escribir un programa en lenguaje C que permita comunicar órdenes existentes sin necesidad de *reprogramarlas*, tal como hace el *shell* (por ejemplo `ls | sort`). En particular, ejecute el siguiente programa que ilustra la comunicación entre proceso padre e hijo a través de un cauce sin nombre redirigiendo la entrada estándar y la salida estándar del padre y el hijo respectivamente.

```c
/*
tarea7.c
Programa ilustrativo del uso de pipes y la redirecci�n de entrada y
salida est�ndar: "ls | sort"
*/

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc, char *argv[])
{
int fd[2];
pid_t PID;

pipe(fd); // Llamada al sistema para crear un pipe

if ( (PID= fork())<0) {
	perror("fork");
	exit(EXIT_FAILURE);
}
if(PID == 0) { // ls
	//Establecer la direccion del flujo de datos en el cauce cerrando
	// el descriptor de lectura de cauce en el proceso hijo
	close(fd[0]);

	//Redirigir la salida estandar para enviar datos al cauce
	//--------------------------------------------------------
	//Cerrar la salida estandar del proceso hijo
	close(STDOUT_FILENO);

	//Duplicar el descriptor de escritura en cauce en el descriptor
	//correspondiente a la salida estandar (stdout)
	dup(fd[1]);
	execlp("ls","ls",NULL);
}
else { // sort. Estoy en el proceso padre porque PID != 0

	//Establecer la direcci�n del flujo de datos en el cauce cerrando
	// el descriptor de escritura en el cauce del proceso padre.
	close(fd[1]);

	//Redirigir la entrada est�ndar para tomar los datos del cauce.
	//Cerrar la entrada est�ndar del proceso padre
	close	(STDIN_FILENO);

	//Duplicar el descriptor de lectura de cauce en el descriptor
	//correspondiente a la entrada est�ndar (stdin)
	dup(fd[0]);
	execlp("sort","sort",NULL);
}

return EXIT_SUCCESS;
}
```

<a name="ejer44"></a>
**Ejercicio 4**. Compare el siguiente programa con el anterior y ejecútelo. Describa la principal diferencia, si existe, tanto en su código como en el resultado de la ejecución.

```c
/*
tarea8.c
Programa ilustrativo del uso de pipes y la redirecci�n de entrada y
salida est�ndar: "ls | sort", utilizando la llamada dup2.
*/

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc, char *argv[])
{
int fd[2];
pid_t PID;

pipe(fd); // Llamada al sistema para crear un pipe

if ( (PID= fork())<0) {
	perror("\nError en fork");
	exit(EXIT_FAILURE);
}
if (PID == 0) { // ls
	//Cerrar el descriptor de lectura de cauce en el proceso hijo
	close(fd[0]);

	//Duplicar el descriptor de escritura en cauce en el descriptor
	//correspondiente a la salida estandr (stdout), cerrado previamente en
	//la misma operacion
	dup2(fd[1],STDOUT_FILENO);
	execlp("ls","ls",NULL);
}
else { // sort. Proceso padre porque PID != 0.
	//Cerrar el descriptor de escritura en cauce situado en el proceso padre
	close(fd[1]);

	//Duplicar el descriptor de lectura de cauce en el descriptor
	//correspondiente a la entrada est�ndar (stdin), cerrado previamente en
	//la misma operaci�n
	dup2(fd[0],STDIN_FILENO);
	execlp("sort","sort",NULL);
}

return EXIT_SUCCESS;
}
```

Ambos programas realizan la misma función, abre un cauce y redireccionan la salida/entrada estándar a dicho cauce, solo que el primero utiliza la función `pip()`, que duplicará el cauce al descriptor mas bajo disponible, que, previamente cerrado, será la *salida/entrada* estándar, mientras que el segundo programa utiliza la función `pip2()`, a la que se le asigna explícitamente el descriptor de la *salida/entrada* estándar, cerrándola en caso de que sea necesario (que lo es).

<a name="ejer45"></a>
**Ejercicio 5**. Este ejercicio se basa en la idea de utilizar varios procesos para realizar partes de una computación en paralelo. Para ello, deberá construir un programa que siga el esquema de computación *maestro-esclavo*, en el cual existen varios procesos trabajadores (esclavos) idénticos y un único proceso que reparte trabajo y reúne resultados (maestro). Cada esclavo es capaz de realizar una computación que le asigne el maestro y enviar a este último los resultados
para que sean mostrados en pantalla por el maestro. El ejercicio concreto a programar consistirá en el cálculo de los números primos que hay en un intervalo. Será necesario construir dos programas, maestro y esclavo. Ten en cuenta la siguiente especificación:
 1. El intervalo de números naturales donde calcular los número primos se pasará como argumento al programa maestro. El maestro creará dos procesos esclavos y dividirá el intervalo en dos subintervalos de igual tamaño pasando cada subintervalo como argumento a cada programa esclavo. Por ejemplo, si al maestro le proporcionamos el intervalo entre 1000 y 2000, entonces un esclavo debe calcular y devolver los números primos comprendidos en el subintervalo entre 1000 y 1500, y el otro esclavo entre 1501 y 2000. El maestro creará dos cauces sin nombre y se encargará de su redirección para comunicarse con los procesos esclavos. El maestro irá recibiendo y mostrando en pantalla (también uno a uno) los números primos calculados por los esclavos en orden creciente.
 2. El programa esclavo tiene como argumentos el extremo inferior y superior del intervalo sobre el que buscará números primos. Para identificar un número primo utiliza el siguiente método concreto: un número n es primo si no es divisible por ningún `k` tal que `2 < k <= sqrt(n)`, donde `sqrt` corresponde a la función de cálculo de la raíz cuadrada (consulte dicha función en el manual). El esclavo envía al maestro cada primo encontrado como un dato entero (4 bytes) que escribe en la salida estándar, la cuál se tiene que encontrar redireccionada a un cauce sin nombre. Los dos cauces sin nombre necesarios, cada uno para comunicar cada esclavo con el maestro, los creará el maestro inicialmente. Una vez que un esclavo haya calculado y enviado (uno a uno) al maestro todos los primos en su correspondiente intervalo terminará.

Solución maestro:

```c
//maestro.c
#define _GNU_SOURCE

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>


int main(int argc, char *argv[]){

  //Comprobamos que se pasan el número de argumentos correcto
  if(argc > 4 || argc < 3){
    printf("Uso: %s <intervalo_inicio(int)> <intervalo_fin(int)> [0<n_hijos<=8 : default 2]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  long int interval_i, interval_f;

  //Comprobamos que los argumentos del intervalo son numéricos y los convertimos
  if( (interval_i=strtol(argv[1], (char**)NULL, 10)) == 0 && errno == EINVAL){
    printf("Error %d en strtol(%s)\n", errno, argv[1]);
    perror("Error en strtol()\n");
    exit(EXIT_FAILURE);
  }else{
    if(errno == ERANGE){
      printf("Number %s set to %li\n", argv[1], interval_i);
      perror("Error en strtol()\n");
      errno=0;
    }
  }
  if( (interval_f=strtol(argv[2], (char**)NULL, 10)) == 0 && errno == EINVAL){
    printf("Error %d en strtol(%s)\n", errno, argv[2]);
    perror("Error en strtol()\n");
    exit(EXIT_FAILURE);
  }else{
    if(errno == ERANGE){
      printf("Number %s set to %li\n", argv[2], interval_f);
      perror("Error en strtol()\n");
      errno=0;
    }
  }

  //Comprobamos que interval_f > interval_i
  if(interval_f <= interval_i){
    printf("Error, <intervalo_inicio(int)> tiene que ser menor que <intervalo_fin(int)>\n");
    exit(EXIT_FAILURE);
  }

  //Creamos los sub-intervalos para los procesos hijoss
  int nP;

  if(argc == 4){
    if( (nP=strtol(argv[3], (char**)NULL, 10)) == 0 && errno == EINVAL){
      printf("Error %d en strtol(%s)\n", errno, argv[2]);
      perror("Error en strtol()\n");
      exit(EXIT_FAILURE);
    }else{
      if(errno == ERANGE){
        printf("Number %s set to %li\n", argv[2], interval_f);
        perror("Error en strtol()\n");
        errno=0;
      }
    }

    if(nP <= 0 | nP > 8){
      printf("Paralelismo por defecto: 2\n");
      nP = 2;
    }
  }else{
    printf("Paralelismo por defecto: 2\n");
    nP = 2;
  }

  size_t nIntervals = nP+1;
  long int intervals[nIntervals];
  long int mid_interval = (interval_f - interval_i)/nP;
  intervals[0] = interval_i;
  intervals[nIntervals-1] = interval_f;
  for(size_t i = 1; i < nIntervals-1; ++i){
    intervals[i] = intervals[i-1] + mid_interval;
  }

  //Vector de cauces
  int fd[nP][2];

  //Creación y asignación de los procesos hijo y creación de cauces
  pid_t PID;
  for (size_t i = 0; i < nIntervals-1; i++) {

    //creamos el cauce
    pipe(fd[i]);

    //Creamos el hijo
    if( (PID=fork()) < 0){
      printf("Error %d en fork()\n", errno);
      perror("Error en fork\n");
      exit(EXIT_FAILURE);
    }

    if( PID == 0 ){
      //Ajuste del cauce en hijo
      close(fd[i][0]); //Cerramos el descriptor de lectura
      dup2(fd[i][1], STDOUT_FILENO); //Redireccionamos a la salida estándar

      //Ejecucion
      char param1[30], param2[30];
      if(i == 0){
        sprintf(param1, "%li", intervals[i]);
        sprintf(param2, "%li", intervals[i+1]);
      }else{
        sprintf(param1, "%li", intervals[i]+1);
        sprintf(param2, "%li", intervals[i+1]);
      }

      if( (execlp("/home/zes/Desktop/SO/SO-P-Todos_MaterialModulo2/Sesion4/ejercicio5_esclavo",
      "ejercicio5_esclavo", param1, param2, (char*)NULL)) < 0 ){
        printf("Error %d en execlp()\n", errno);
        perror("Error en exceclp()\n");
        exit(EXIT_FAILURE);
      }

    }else{
      //Ajuste del cauce padre
      close(fd[i][1]); //Cerramos el descriptor de escritura
      dup2(fd[i][0], STDIN_FILENO); //Redireccionamos a la entrada estándar
      if(i == 0){
        printf("Intervalo %lu: [%li, %li] ===> hijo(%u)\n", i+1, intervals[i], intervals[i+1], PID);
      }else{
        printf("Intervalo %lu: [%li, %li] ===> hijo(%u)\n", i+1, intervals[i]+1, intervals[i+1], PID);
      }

      //Recibir números y mostrarlos por consola
      printf("Números primos:\n");
      char buf[20];
      for(size_t i = 0; i < 1;){
        fgets(buf, 20, stdin);
        if(strcmp(buf, "END\n") == 0){
          ++i;
        }else{
          printf("%s", buf);
        }
      }
    }
  }

  return EXIT_SUCCESS;
}
```

Solución esclavo:

```c
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<math.h>

int es_primo(long int);

int main(int argc, char *argv[]){
  if(argc != 3){
    printf("Uso: %s <intervalo_inicio> <intervalo_fin>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  long int interval_i, interval_f;

  if( (interval_i=strtol(argv[1], (char**)NULL, 10)) == 0 && errno == EINVAL){
    printf("Error %d en strtol(%s)\n", errno, argv[1]);
    perror("Error en strtol()\n");
    exit(EXIT_FAILURE);
  }else{
    if(errno == ERANGE){
      printf("Number %s set to %li\n", argv[1], interval_f);
      perror("Error en strtol()\n");
      errno=0;
    }
  }

  if( (interval_f=strtol(argv[2], (char**)NULL, 10)) == 0 && errno == EINVAL){
    printf("Error %d en strtol(%s)\n", errno, argv[2]);
    perror("Error en strtol()\n");
    exit(EXIT_FAILURE);
  }else{
    if(errno == ERANGE){
      printf("Number %s set to %li\n", argv[2], interval_f);
      perror("Error en strtol()\n");
      errno=0;
    }
  }
  for(long int i = interval_i; i < interval_f; ++i){
    if(es_primo(i)){
      printf("%li\n", i);
    }
  }
  printf("END\n");
  return EXIT_SUCCESS;
}

int es_primo(long int n){

  long int max = (long int)sqrt(n);
  for(long int i = 2; i <= max; ++i){
    if(n%i == 0){
      return 0;
    }
  }

  return 1;
}
```

---

<a name="sesion5"></a>
### Sesión 5

---
