# MBEE
Metric Buttload Encryption Engine

This encryption utility should be used by Unix Admins who need to encrypt backups for long term storage.  It uses the OPENSSL engine which must be installed on the unix machine encrypting or decrypting.

MBEE uses 4 types of encryption to encrypt your files.
aes-256-cbc
bf-ecb
camellia-256-cfb1
aes-192-ecb

MBEE forces 128char passwords on the passwords used to encrypt a file.  The only password the user enters is to unlock the mbee_keystore.

08/2018
Development continues of the engine.
