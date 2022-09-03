FROM mcr.microsoft.com/mssql/server:2019-latest

USER root

COPY createdb.sql createdb.sql
COPY createdb.sh createdb.sh
COPY entrypoint.sh entrypoint.sh

RUN chmod +x entrypoint.sh

CMD /bin/bash ./entrypoint.sh
