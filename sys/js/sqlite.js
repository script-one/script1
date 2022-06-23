import * as sqlite from 'https://deno.land/x/sqlite/mod.ts'

export class Sqlite {
    constructor(file) {
        this.db = new sqlite.DB(file)
    }

    query(sql, params) {
        return this.db.query(sql, params)
    }

    close() {
        this.db.close()
    }
}
