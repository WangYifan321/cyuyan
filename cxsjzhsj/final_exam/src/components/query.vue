<template>
  <div style="margin-top: 100px">
    <center>
      <el-input v-model="name" placeholder="请输入您的姓名" style="width: 80%;" ></el-input>

      <el-input v-model="input" placeholder="请输入您的身份证号，查询是否申请成功" style="width: 80%;margin-top: 30px" ></el-input>
      <el-button type="primary" @click="doSearch()" id="login">点击查询</el-button>
    </center>
  </div>
</template>

<script>
import {searchOutsiders} from "../apis/api";
import {get_search_token} from "../apis/api";
import {mapMutations} from "vuex";

export default {
  name: "search",
  data(){
    return{
      input: '',
      content: '',
      date1: '2016-05-02 21:21:32',
      date2: '2017-09-13 21:18:21',
      gender: '男',
      phone: '12322214568',
      id_card: '71892891716227161721',
      guarantor_name: '哈哈',
      affected: '否',
      cough: '否',
      health_code: '绿',
      unit_info: '杭电',
      cause: '吃饭啊',
      name: ''
    }
  },
  methods: {
    ...mapMutations(['changeLogin']),
    doSearch(){
      let i_url = '/apis/outsiders/token'
      let i_params = {name:this.name,ID_card:this.input}
      get_search_token(i_url,i_params).then(res =>{
        this.changeLogin({Authorization: res.data.token})
      })
      let url = '/apis/outsiders/search?ID_card='+this.input
      let params = {}
      searchOutsiders(url,params).then(res => {
         if(res !== null) {
           let content = res[0]
           let info = "姓名: " + content.name +'</p><p>'+ '身份证号: '+content.ID_card+'</p><p>'+ '担保人: ' +content.guarantor_name +'</p><p>' + '申请进入时间: ' +content.apply_entry
           + '</p><p>'+'申请离开时间: ' + content.apply_leave
           if(content.pass === 0){
             info += '</p><p>' + '状态: 正在审核'
           }else{
             info += '</p><p>' + '状态: 审核通过'

           }
           this.$alert(info, {
             dangerouslyUseHTMLString: true,
             showClose: false
           })
         }else{
           this.$alert("抱歉，无相关信息")
         }
      })

    }
  }
}
</script>

<style scoped>

#login {
  width: 300px;
  background-color: #06f;
  margin-top: 20px;
}

</style>
<style>
.el-message-box{
  width: 80% !important;
}
</style>
