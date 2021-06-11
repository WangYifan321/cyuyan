import Vue from 'vue'
import Router from 'vue-router'
import Notfound from '../views/notfound'
import User from '../views/user_index'
import Admin from '../views/admin_index'
import Guarantee from '../views/guarantee_index'
import Guarantor_Login from '../views/guarantor_login'
import Query from '../components/query'
import Form from '../components/userForm'
import Guarantor_Register from '../views/guarantor_register'
import Admin_Login from '../views/admin_login'
import Admin_Register from '../views/admin_register'
Vue.use(Router)

const router = new Router({
  routes:[
    {
      path: '/',
      component: User,
      children: [
        {
          path: 'query',
          name: 'query',
          component: Query

        },{
          path: 'form',
          name: 'form',
          component: Form
        }
      ]
    },{
      path: '/admin',
      component: Admin
    },{
      path: '/guarantee',
      component: Guarantee

    },{
      path: '/guarantor_login',
      component: Guarantor_Login
    },
    {
      path: '/register_guarantor',
      component: Guarantor_Register
    },{
      path: '/register_admin',
      component: Admin_Register
    },
    {
      path: '/admin_login',
      component: Admin_Login
    },
    {
      path: '*',
      component: Notfound
    }
  ],
  mode: 'history'
});
// 导航守卫
// 使用 router.beforeEach 注册一个全局前置守卫，判断用户是否登陆
router.beforeEach((to, from, next) => {
  if (to.path === '/guarantor_login' || to.path === '/' || to.path === '/form' || to.path ==='/query' || to.path === '/register_guarantor' || to.path === '/admin_login' || to.path === 'register_admin') {
    next();
  } else {
    let token = localStorage.getItem('Authorization');

    if (token === null || token === '') {
      next('/login');
    } else {
      next();
    }
  }
});
export default router
