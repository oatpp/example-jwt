CREATE EXTENSION IF NOT EXISTS "uuid-ossp";
CREATE EXTENSION IF NOT EXISTS "pgcrypto";

CREATE TABLE users (
    id                      varchar (36) PRIMARY KEY,
    username                varchar (256) NOT NULL,
    email                   varchar (256) NOT NULL,
    pswhash                 varchar (256) NOT NULL,

    CONSTRAINT              UK_USERS_USERNAME UNIQUE (username),
    CONSTRAINT              UK_USERS_EMAIL UNIQUE (email)
);

INSERT INTO users
(id, username, email, pswhash) VALUES ('4bb48865-1a84-49c7-94eb-148ed2f9d7a5', 'admin', 'admin@domain.com', crypt('admin', gen_salt('bf', 8)));
