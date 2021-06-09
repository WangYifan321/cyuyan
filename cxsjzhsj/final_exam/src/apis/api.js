import {post} from './http.js'
import {get} from './http.js'
export function
 submitForm(params){
  return post('/apis/outsiders',params)
}
export function
 login(params) {
  return post('/apis/guarantor/token',params)
}
export function
 searchOutsiders(url,params) {
  return get(url,params)
}
export function
 register_guarantor(params) {
  return post('/apis/guarantor',params)
}
export function
 admin_register(params) {
  return post('/apis/admin',params)
}
export function
 admin_login(params) {
  return post('/apis/admin/token',params)
}
export function
 admin_get(params) {
  return get('/apis/outsiders',params)
}

