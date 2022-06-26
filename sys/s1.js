export * from './js/base.js'
export * from './js/date.js'
export * from './js/math.js'
export * from './js/console.js'
export * from './js/json.js'
export * from './js/copy.js'
export * from './js/func.js'
import * as io from './js/io.js'
import * as re from './js/regexp.js'
import { hash } from './js/hash.js'
import { Sqlite } from './js/sqlite.js'
import { Server } from './js/server.js'
global.hash = hash
global.Sqlite = Sqlite
global.Server = Server
