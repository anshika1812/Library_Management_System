FROM gcc:latest

WORKDIR /app

COPY . .

RUN gcc -o lms main.c

CMD ["./lms"]
