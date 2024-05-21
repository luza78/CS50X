CREATE TABLE stocks (
    id INTEGER NOT NULL,
    user_id INTEGER NOT NULL,
    name TEXT NOT NULL,
    quantity_owned INTEGER NOT NULL,
    FOREIGN KEY(user_id) REFERENCES users(id)
    PRIMARY KEY(id)
);

CREATE TABLE history (
    stock_id INTEGER NOT NULL,
    user_id INTEGER NOT NULL,
    type TEXT DEFAULT "Buy",
    transaction_time DATETIME NOT NULL DEFAULT (strftime('%Y-%m-%d %H:%M:%S', 'now', 'localtime')),
    quantity INTEGER NOT NULL,
    price numeric NOT NULL,
    FOREIGN KEY(user_id) REFERENCES users(id)
    FOREIGN KEY(stock_id) REFERENCES stocks(id)
);