#!/bin/bash

SCRIPT_DIRECTORY=`( cd -P $(dirname $0); pwd)`
WEB_DIR="${SCRIPT_DIRECTORY}/../web/"
TMP_DIR="${SCRIPT_DIRECTORY}/tmp/"
RESSOURCES_DIR="${SCRIPT_DIRECTORY}/../src/ressources/"

mkdir -p "${TMP_DIR}"
if [ $? -ne 0 ]; then
    exit 1
fi

# Génération du javascript
cat ${WEB_DIR}js/jquery.min.js > ${TMP_DIR}build.js
cat ${WEB_DIR}js/base64.js >> ${TMP_DIR}build.js
cat ${WEB_DIR}js/url.js >> ${TMP_DIR}build.js
cat ${WEB_DIR}js/hash.js >> ${TMP_DIR}build.js
cat ${WEB_DIR}js/beautiful.js >> ${TMP_DIR}build.js
cat ${WEB_DIR}js/ip.js >> ${TMP_DIR}build.js
cat ${WEB_DIR}js/quoted.printable.js >> ${TMP_DIR}build.js
cat ${WEB_DIR}js/html.js >> ${TMP_DIR}build.js

java -jar ${SCRIPT_DIRECTORY}/yuicompressor-2.4.7.jar --charset utf-8 --type js -o ${TMP_DIR}scripts.min.js ${TMP_DIR}build.js

js_content=`cat ${TMP_DIR}scripts.min.js`

rm -f ${TMP_DIR}build.js
rm -f ${TMP_DIR}scripts.min.js


# Génération du CSS
java -jar ${SCRIPT_DIRECTORY}/yuicompressor-2.4.7.jar --charset utf-8 --type css -o ${TMP_DIR}css.min.css ${WEB_DIR}css/style.css

css_content=`cat ${TMP_DIR}css.min.css`

rm -f ${TMP_DIR}css.min.css


# Génération du code HTML pour framareseau
cat ${WEB_DIR}index.html > ${TMP_DIR}index.html
perl -pi -e "s/<script type=\"text\/javascript\" src=\"js\/jquery\.min\.js\"><\/script>//msg" ${TMP_DIR}index.html
perl -pi -e "s/<script type=\"text\/javascript\" src=\"js\/base64\.js\"><\/script>//msg" ${TMP_DIR}index.html
perl -pi -e "s/<script type=\"text\/javascript\" src=\"js\/url\.js\"><\/script>//msg" ${TMP_DIR}index.html
perl -pi -e "s/<script type=\"text\/javascript\" src=\"js\/hash\.js\"><\/script>//msg" ${TMP_DIR}index.html
perl -pi -e "s/<script type=\"text\/javascript\" src=\"js\/beautiful\.js\"><\/script>//msg" ${TMP_DIR}index.html
perl -pi -e "s/<script type=\"text\/javascript\" src=\"js\/ip\.js\"><\/script>//msg" ${TMP_DIR}index.html
perl -pi -e "s/<script type=\"text\/javascript\" src=\"js\/quoted\.printable\.js\"><\/script>//msg" ${TMP_DIR}index.html
html_content=`cat ${TMP_DIR}index.html`
search_js="<script type=\"text/javascript\" src=\"js/html.js\"></script>"
replace_js="<script type=\"text/javascript\">${js_content}</script>"
echo ${html_content/${search_js}/${replace_js}} > ${TMP_DIR}index.html

perl -pi -e "undef $/; s/<link rel=\"stylesheet\" href=\"css\/style\.css\" \/>/<style>${css_content}<\/style>/msg" ${TMP_DIR}index.html
java -jar ${SCRIPT_DIRECTORY}/htmlcompressor-1.5.2.jar ${TMP_DIR}index.html > ${TMP_DIR}index.min.html
rm -f ${TMP_DIR}index.html
mv ${TMP_DIR}index.min.html ${RESSOURCES_DIR}index.html

rmdir "${TMP_DIR}"