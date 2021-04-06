package main

import (
	"context"
	"fmt"
	"html/template"
	"log"
	"math/rand"
	"net/http"
	"os"
	"time"

	"go.mongodb.org/mongo-driver/bson"
	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
	"golang.org/x/crypto/argon2"
)

var (
	dbConnString     = "mongodb://127.0.0.1:27017"
	minimumTimestamp = int64(1577836800000) // The smallest timestamp for snowflake generation (Jan 01, 2020 - 00:00:00 UTC)
	seedCharset      = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-_"
)

type Template struct {
	Keys map[string]byte // keyed strings with byte data
}

type Account struct {
	_id      int64
	username string
	password []byte
}

// --- Database Functions --- //

func dbConn(uri string) (*mongo.Client, context.Context) {
	client, err := mongo.NewClient(options.Client().ApplyURI(uri))
	if err != nil {
		log.Fatal(err)
	}

	ctx, cancel := context.WithTimeout(context.Background(), 10000000000) // 10s == 1e10ns
	defer cancel()

	err = client.Connect(ctx)
	if err != nil {
		log.Fatal(err)
	}

	err = client.Ping(context.TODO(), nil)
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println("Database connected!")
	return client, ctx
}

func dbClose(client *mongo.Client, ctx context.Context) {
	client.Disconnect(ctx)

	err := client.Ping(context.TODO(), nil)
	if err == nil {
		fmt.Println("Unable to disconnect database connection!")
		os.Exit(1)
	}

	fmt.Println("Database disconnected!")
}

func createPost(title string, content []byte, first bool) {
	client, ctx := dbConn(dbConnString)
	posts := client.Database("forum").Collection("posts")
	snowflake := getSnowflake(getUnixTime())

	_, err := posts.InsertOne(ctx, bson.M{"_id": snowflake, "title": title, "content": content, "thread": first})
	if err != nil {
		log.Fatal(err)
	}

	defer dbClose(client, ctx)
}

func updatePost(id int64, title string, content []byte) {
	client, ctx := dbConn(dbConnString)
	posts := client.Database("forum").Collection("posts")

	_, err := posts.UpdateOne(ctx, bson.M{"_id": id}, bson.M{"title": title, "content": content})
	if err != nil {
		log.Fatal(err)
	}

	defer dbClose(client, ctx)
}

func deletePost(id int64) {
	client, ctx := dbConn(dbConnString)
	posts := client.Database("forum").Collection("posts")

	_, err := posts.DeleteOne(ctx, bson.M{"_id": id})
	if err != nil {
		log.Fatal(err)
	}

	defer dbClose(client, ctx)
}

func createUserAccount(username string, password []byte) int64 {
	client, ctx := dbConn(dbConnString)
	users := client.Database("forum").Collection("users")

	snowflake := getSnowflake(getUnixTime())
	salt := getSalt(16, seedCharset)
	key := argon2.IDKey(password, salt, 1, 65536, 4, 32)

	_, err := users.InsertOne(ctx, Account{snowflake, username, key})
	if err != nil {
		log.Fatal(err)
	}

	defer dbClose(client, ctx)
	return snowflake
}

func updateUserAccount(id int64, username string, password []byte) {
	client, ctx := dbConn(dbConnString)
	users := client.Database("forum").Collection("users")

	salt := getSalt(16, seedCharset)
	key := argon2.IDKey(password, salt, 1, 65536, 4, 32)

	_, err := users.UpdateOne(ctx, bson.M{"_id": id}, bson.M{"username": username, "password": key})
	if err != nil {
		log.Fatal(err)
	}

	defer dbClose(client, ctx)
}

func deleteUserAccount(id int64) {
	client, ctx := dbConn(dbConnString)
	users := client.Database("forum").Collection("users")

	_, err := users.DeleteOne(ctx, bson.M{"_id": id})
	if err != nil {
		log.Fatal(err)
	}

	defer dbClose(client, ctx)
}

// --- Template Rendering Functions --- //

func getTemplateFile(name string) string {
	return "./templates/" + name + ".html"
}

func renderTemplate(w http.ResponseWriter, name string, tmp *Template) {
	f := getTemplateFile(name)
	t := template.Must(template.ParseFiles(f))
	e := t.ExecuteTemplate(w, f, tmp)

	if e != nil {
		http.Error(w, e.Error(), http.StatusInternalServerError)
	}
}

// --- Miscellaneous Functions --- //

func getUnixTime() int64 {
	return time.Now().UTC().UnixNano()
}

func getSalt(length uint, charset string) []byte {
	rand.Seed(getUnixTime())
	b := make([]byte, length)

	for i := range b {
		b[i] = charset[rand.Intn(len(charset))]
	}

	return b
}

func getSnowflake(timestamp int64) int64 {
	return (timestamp - minimumTimestamp) << 22
}

func getTimestamp(snowflake int64) int64 {
	return (snowflake >> 22) + minimumTimestamp
}

func main() {
	id := createUserAccount("dracovian", []byte("onomatopoeia"))
	fmt.Println("User ID:", id)
}
