The following steps must be taken for the example script to work.

0. Create wallet
0. Create account for enumivo.token
0. Create account for scott
0. Create account for exchange
0. Set token contract on enumivo.token
0. Create ENU token
0. Issue initial tokens to scott

**Note**:
Deleting the `transactions.txt` file will prevent replay from working.


### Create wallet
`enucli wallet create`

### Create account steps
`enucli create key`

`enucli create key`

`enucli wallet import <private key from step 1>`

`enucli wallet import <private key from step 2>`

`enucli create account enumivo <account_name> <public key from step 1> <public key from step 2>`

### Set contract steps
`enucli set contract enumivo.token /contracts/enumivo.token -p enumivo.token@active`

### Create ENU token steps
`enucli push action enumivo.token create '{"issuer": "enumivo.token", "maximum_supply": "100000.0000 ENU", "can_freeze": 1, "can_recall": 1, "can_whitelist": 1}' -p enumivo.token@active`

### Issue token steps
`enucli push action enumivo.token issue '{"to": "scott", "quantity": "900.0000 ENU", "memo": "testing"}' -p enumivo.token@active`
