config = {
    database: 'client1',
    host: '192.168.43.220',
    user:'User',
    password:'123',
    logging:false,
    trustServerCertificate: true,
    dialect: 'mssql',
    dialectOptions: {
        useUTC: false,
        dateFirst: 1,
    },
    pool: {
        max: 5,
        min: 0,
        idle: 10000
    }
}

exports.config = config;