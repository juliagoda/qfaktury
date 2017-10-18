 #!/bin/bash

cd "$1/.local/share/data/elinux/gus"
curl -s https://getcomposer.org/installer | php
php composer.phar install

exit

