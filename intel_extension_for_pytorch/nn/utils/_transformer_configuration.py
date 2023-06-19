import torch 

class IPEXTransformerConfig():
    def __init__(self,
                 embed_dim = 4096,
                 intermediate_size = None,
                 num_attention_heads = 16,
                 max_positions = 4096,
                 rotary_embedding_class = "GPTJRotaryEmbedding",
                 rotary_dim = 64,
                 rotate_half = False,
                 rotate_every_two = True,
                 use_casual_mask = False,
                 activation_function = 'gelu_new',
                 norm_eps = 0.001,
                 residual_dropout = None,
                 attn_dropout = None,
                 enable_bias = False,
                 residual_pdrop = None,
                 scale_attention = False,
                 is_decoder = False,
                 do_norm_before = False,
                 ln_elementwise_affine = False,
                 seq_first = False,
                 kv_cache_optimize = False,
                 positional_embedding_base = 10000,
                 sdp_fusion_enable = True,
                 device = "cpu",
                 dtype = torch.half
                #  opt_drop_out = 1.0
                 ) -> None:
        self.embed_dim = embed_dim
        self.intermediate_size = intermediate_size
        self.num_attention_heads = num_attention_heads
        self.max_positions = max_positions
        self.rotary_embedding_class = rotary_embedding_class
        self.rotary_dim = rotary_dim
        self.rotate_half = rotate_half
        self.rotate_every_two = rotate_every_two
        self.use_casual_mask = use_casual_mask
        self.activation_function = activation_function
        self.norm_eps = norm_eps
        self.residual_dropout = residual_dropout
        self.attn_dropout = attn_dropout
        self.enable_bias = enable_bias
        self.residual_pdrop = residual_pdrop
        self.scale_attn = scale_attention # gptj and llama will need to scale attention weight
        self.is_decoder = is_decoder # opt parameter
        self.do_norm_before = do_norm_before
        self.ln_elementwise_affine = ln_elementwise_affine
        self.kv_cache_optimize = kv_cache_optimize
        self.seq_first = seq_first
        self.positional_embedding_base = positional_embedding_base
        self.sdp_fusion_enable = sdp_fusion_enable
        self.device = device
        self.dtype = dtype