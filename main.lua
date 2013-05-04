
--  使用 send_channel_message 将消息发回频道.
--  send_channel_message('test')


-- 每当频道有消息发生, 就调用这个函数.
-- 注意, 不要在这里阻塞, 会导致整个 avbot 都被卡住
-- 因为 avbot 是单线程程序.
function channel_message(jsonmsg)
	print(jsonmsg)
end
