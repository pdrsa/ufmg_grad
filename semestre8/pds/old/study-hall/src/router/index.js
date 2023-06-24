import Vue from 'vue'
import VueRouter from 'vue-router'

Vue.use(VueRouter)

const routes = [
  {
    path: '/register',
    name: 'register',
    component: () => import('../components/RegisterPage.vue'),
  },
  {
    path: '/group',
    name: 'group',
    component: () => import('../components/GroupPage.vue'),
  },
  {
    path: '/registerGroup',
    name: 'registerGroup',
    component: () => import('../components/RegisterGroupPage.vue'),
  },
  {
    path: '/user',
    name: 'user',
    component: () => import('../components/UserPage.vue'),
  },
  {
    path: '/search',
    name: 'search',
    component: () => import('../components/SearchPage.vue'),
  },
  {
    path: '/login',
    name: 'login',
    component: () => import('../components/LoginPage.vue'),
  },
  {
    path: '/',
    name: 'home',
    component: () => import('../components/HomePage.vue'),
  },
  {
    path: '/home',
    name: 'home',
    component: () => import('../components/HomePage.vue'),
  }
]

const router = new VueRouter({
  mode: 'history',
  routes
})

export default router
