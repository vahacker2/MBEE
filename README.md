# MBEE
Metric Buttload Encryption Engine


This encryption utility should be used by Unix Admins who need to encrypt backups for long term storage.  It uses the OPENSSL engine which must be installed on the unix machine encrypting or decrypting.

MBEE uses 4 types of encryption to encrypt your files.<br>
aes-256-cbc<br>
bf-ecb<br>
camellia-256-cfb1<br>
aes-192-ecb<br>

MBEE forces 128char passwords on the passwords used to encrypt a file.   The only password the user enters is to unlock the mbee_keystore.

Installation: Download mbee.c source file <br>
make mbee source file name <br>
copy mbee into one of your paths<br>

08/12/2018
- Turned off echo so passwords would not be shown when entered.
- Improvement to user interface.
- Zeroed out password variables after use.

<br>
<br>=======

>>>>>>> b5b6a6ed19b78d2485d3082284c9fd82cb008bf7
